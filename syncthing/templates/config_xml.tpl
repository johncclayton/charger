<configuration version="16">
 <folder id="dvmxe-dvkvn" label="charger_source" path="/data/charger/" type="readwrite" rescanIntervalS="2" ignorePerms="false" autoNormalize="true">
        {% for device in devices %}
        <device id="{{device.id}}"></device>
        {% endfor %}
        <minDiskFreePct>1</minDiskFreePct>
        <versioning></versioning>
        <copiers>0</copiers>
        <pullers>0</pullers>
        <hashers>0</hashers>
        <order>random</order>
        <ignoreDelete>false</ignoreDelete>
        <scanProgressIntervalS>0</scanProgressIntervalS>
        <pullerSleepS>0</pullerSleepS>
        <pullerPauseS>0</pullerPauseS>
        <maxConflicts>10</maxConflicts>
        <disableSparseFiles>false</disableSparseFiles>
        <disableTempIndexes>false</disableTempIndexes>
    </folder>
    {% for device in devices %}
    <device id="{{device.id}}" name="{{device.name}}" compression="metadata" introducer="false">
        <address>{{device.address}}</address>
    </device>
    {% endfor %}
    <gui enabled="true" tls="false" debugging="false">
        <address>0.0.0.0:8384</address>
        <user>charger</user>
        <password>$2a$10$n37Lq/1ZKtcQzl7HEaYGUe/jioAS3wLh4ZZYshtz6wmt.zi0JWe6e</password>
        <apikey>QhoZnkdCcGGyntP4QSbZZPR9RjtYzSYK</apikey>
        <theme>dark</theme>
    </gui>
    <options>
        <listenAddress>tcp4://0.0.0.0</listenAddress>
        <globalAnnounceServer>default</globalAnnounceServer>
        <globalAnnounceEnabled>true</globalAnnounceEnabled>
        <localAnnounceEnabled>true</localAnnounceEnabled>
        <localAnnouncePort>21027</localAnnouncePort>
        <localAnnounceMCAddr>[ff12::8384]:21027</localAnnounceMCAddr>
        <maxSendKbps>0</maxSendKbps>
        <maxRecvKbps>0</maxRecvKbps>
        <reconnectionIntervalS>60</reconnectionIntervalS>
        <relaysEnabled>true</relaysEnabled>
        <relayReconnectIntervalM>10</relayReconnectIntervalM>
        <startBrowser>false</startBrowser>
        <natEnabled>true</natEnabled>
        <natLeaseMinutes>60</natLeaseMinutes>
        <natRenewalMinutes>30</natRenewalMinutes>
        <natTimeoutSeconds>10</natTimeoutSeconds>
        <urAccepted>0</urAccepted>
        <urUniqueID></urUniqueID>
        <urURL>https://data.syncthing.net/newdata</urURL>
        <urPostInsecurely>false</urPostInsecurely>
        <urInitialDelayS>1800</urInitialDelayS>
        <restartOnWakeup>true</restartOnWakeup>
        <autoUpgradeIntervalH>12</autoUpgradeIntervalH>
        <keepTemporariesH>24</keepTemporariesH>
        <cacheIgnoredFiles>false</cacheIgnoredFiles>
        <progressUpdateIntervalS>5</progressUpdateIntervalS>
        <symlinksEnabled>true</symlinksEnabled>
        <limitBandwidthInLan>false</limitBandwidthInLan>
        <minHomeDiskFreePct>1</minHomeDiskFreePct>
        <releasesURL>https://upgrades.syncthing.net/meta.json</releasesURL>
        <overwriteRemoteDeviceNamesOnConnect>false</overwriteRemoteDeviceNamesOnConnect>
        <tempIndexMinBlocks>10</tempIndexMinBlocks>
    </options>
</configuration>
