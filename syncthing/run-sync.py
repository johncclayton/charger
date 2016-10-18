from docker import Client
import argparse, os

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--image", type=str, help="the name of the docker image to run")
parser.add_argument("-n", "--name", type=str, help="the resulting name of the container")
parser.add_argument("-r", "--root", type=str, default=os.path.abspath(os.path.join(__file__, '..', '..')),
                    help="the root directory to map to the sync source")
args = parser.parse_args()

print("Using root: ", args.root)

if args.image and args.name and args.root:
    client = Client()
    container = client.create_container(image=args.image,
                                        name=args.name,
                                        volumes=['/data/charger'],
                                        ports=[22000, (21027, 'udp'), 8384],
                                        host_config=client.create_host_config(
                                            binds=['%s:/data/charger' % (args.root,)],
                                            port_bindings={
                                                22000: 22000,
                                                '21027/udp': 21027,
                                                8384: 8384
                                            }))
    client.start(container.get('Id'))
    print("Container %s started" % (args.name,))
else:
    print("You must specify an image name to start")
