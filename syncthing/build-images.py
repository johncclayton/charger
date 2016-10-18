from jinja2 import Environment, FileSystemLoader
from docker import Client
import os, shutil, tarfile, io
import xml.etree.ElementTree as ET
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-u", "--update", action='store_true', help="force recreate the keys")
args = parser.parse_args()

client = Client()

HOSTS = {
    "rpi3": "hypriot",
    "win-dev": "alpine",
    "mac-dev": "alpine"
}

# build/run the syncthing_cli image to get the configuration
key_pathname = os.path.join(os.getcwd(), "keys")

if args.update:
    key_container = client.create_container("johncclayton/syncthing-cli", "/generate-identities.sh",
                                            environment={
                                                "KEY_HOSTS": " ".join(HOSTS.keys())
                                            })
    print("Generating keys...")
    key_response = client.start(container=key_container.get('Id'))
    client.wait(container=key_container.get('Id'))

    # now copy the files from within the container to the local disk
    if os.path.exists(key_pathname):
        shutil.rmtree(key_pathname)

    os.mkdir(key_pathname)

    print("Copying key data from container...")
    strm, stat = client.get_archive(key_container, "/keys")
    data = io.BytesIO(strm.read())
    tarobj = tarfile.open(fileobj=data)
    tarobj.extractall(path=os.getcwd())

# find the syncthing config.xml template and populate it with all the known device Ids.  This
# file is then used within all the syncthing images to ensure that all hosts know about each other.
env = Environment(loader=FileSystemLoader(os.path.join(os.getcwd(), "templates")))
config_template = env.get_template('config_xml.tpl')

devices = []

print("Creating config.xml for each device...")

# create a single config.xml file that has the ID values of every known key
for subdir, dirs, files in os.walk(key_pathname):
    for d in dirs:
        full_path = os.path.join(subdir, d)
        e = ET.parse(os.path.join(full_path, "config.xml")).getroot()
        the_id = e.findall("./device")[0].attrib['id']
        the_name = d
        if the_id is not None and the_name is not None:
            docker_name = the_name
            docker_name.replace('_', '-')

            devices.append({
                "name": the_name,
                "id": the_id,
                "docker_name": docker_name,
                "docker_type": HOSTS[the_name],
                "address": "dynamic"
            })

            # create a Dockerfile for syncthing for each device that is being used.  we need to find the right template
            # and populate only the correct key_name value so that the appropriate keys/PEM files can be located.
            dockerfile_template = env.get_template('Dockerfile_' + HOSTS[the_name] + '.tpl')
            df = open(os.path.join(key_pathname, the_name, 'Dockerfile'), 'w')
            df.write(dockerfile_template.render(key_name=the_name))
            df.close()

config_xml = config_template.render(devices=devices)
config_xml_path = os.path.join(key_pathname, 'config.xml')
xml = open(config_xml_path, 'w')
xml.write(config_xml)
xml.close()

for obj in devices:
    shutil.copy(config_xml_path, os.path.join(key_pathname, obj["name"]))

os.remove(config_xml_path)

print("Creating docker-compose.yml file...")

# create a docker-compose.yml file - this will help to make building all the images a bit easier
compose_template = env.get_template('docker-compose.tpl')
compose_filename = os.path.join(key_pathname, "docker-compose.yml")
compose = open(compose_filename, 'w')
compose.write(compose_template.render(devices=devices))
compose.close()

print("Done! Check the keys/docker-compose.yml file for services that can be built.")