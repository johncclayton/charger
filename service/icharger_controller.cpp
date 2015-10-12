#include <QDebug>
#include <QThread>
#include <QVariantMap>

#include "icharger_controller.h"
#include "icharger/icharger_message_keys.h"
#include "usb/icharger_data.h"
#include "json_helper.h"

struct DeviceOnlyJson {
    QVariantMap toVariantMap(device_only& d) const {
        QVariantMap data;
        
        data[STR_DEVICE_ONLY_ID] = d.device_id.value;
        data[STR_DEVICE_ONLY_SERIAL_NUMBER] = QString::fromLatin1((const char*)d.device_sn, 12).trimmed();
        data[STR_DEVICE_ONLY_HW_VERSION] = d.hw_version.value / 1000.0;
        data[STR_DEVICE_ONLY_SW_VERSION] = d.sw_version.value / 1000.0;
        data[STR_DEVICE_ONLY_CH1_STATUS] = d.ch1_status.value;
        data[STR_DEVICE_ONLY_CH2_STATUS] = d.ch2_status.value;
        
        return data;
    }
};

struct ChannelStatusJson {
    QVariantMap toVariantMap(channel_status& c, int channel) const {
        QVariantMap data;
        
        data[STR_CHANNEL_STATUS_CHANNEL_NUM] = channel;
        data[STR_CHANNEL_STATUS_OUTPUT_POWER] = quint32(c.output_power.value);
        data[STR_CHANNEL_STATUS_OUTPUT_CURRENT] = c.output_current.value;
        data[STR_CHANNEL_STATUS_OUTPUT_VOLTAGE] = c.output_voltage.value / 1000.0;
        data[STR_CHANNEL_STATUS_OUTPUT_CAPACITY] = quint32(c.output_capacity.value);
        
        data[STR_CHANNEL_STATUS_INPUT_VOLTAGE] = c.input_voltage.value / 1000.0;
        data[STR_CHANNEL_STATUS_TEMP_INTERNAL] = c.temp_internal.value / 10.0;
        data[STR_CHANNEL_STATUS_TEMP_EXTERNAL] = c.temp_external.value / 10.0;
        
        QVariantList cells;
        for(int index = 0; index < MAX_CELLS; ++index) {
            if(c.cell_voltage[index] == 1024 && c.cell_resistance[index] == 1024)
                continue;
            
            QVariantMap cell;
            cell[STR_CHANNEL_STATUS_CELL_NUMBER] = index;
            cell[STR_CHANNEL_STATUS_CELL_VOLTAGE] = ((double)c.cell_voltage[index]) / 1000.0;
            cell[STR_CHANNEL_STATUS_CELL_BALANCE_STATUS] = c.balance_status[index];
            cell[STR_CHANNEL_STATUS_CELL_RESISTANCE] = c.cell_resistance[index];
            cells << cell;
        }    
        
        data[STR_CHANNEL_STATUS_CELLS] = cells;
        
        data[STR_CHANNEL_STATUS_TOTAL_RESISTANCE] = c.total_resistance;
        data[STR_CHANNEL_STATUS_LINE_INTERNAL_RESISTANCE] = c.line_internal_resistance;
        data[STR_CHANNEL_STATUS_CYCLE_COUNT] = c.cycle_count;
        data[STR_CHANNEL_STATUS_CONTROL_STATUS] = c.control_status;
        data[STR_CHANNEL_STATUS_RUN_STATUS] = c.run_status;
        data[STR_CHANNEL_STATUS_RUN_ERROR] = c.run_error;
        data[STR_CHANNEL_STATUS_DIALOG_BOX_ID] = c.dialog_box_id;
        
        return data;
    }
};

iCharger_DeviceController::iCharger_DeviceController(QString key, icharger_usb_ptr p, QObject *parent) : 
    QObject(parent), _key(key), _device(p)
{
    // query status of every bloody thing every second
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    _timer->start(750);
}

iCharger_DeviceController::~iCharger_DeviceController() {
    qDebug() << "bye bye device controller";
    _timer->deleteLater();
    _timer = 0;
}

void iCharger_DeviceController::handleTimeout() {
    bool changed = false;
    
    // fetch device status and publish on the bus
    device_only d;
    int r = _device->get_device_only(&d);
    if(r == 0) {
        DeviceOnlyJson device;
        QVariantMap t = device.toVariantMap(d);
        t[STR_DEVICE_ONLY_MANUFACTURER] = _device->manufacturer();
        t[STR_DEVICE_ONLY_PRODUCT] = _device->product();
        
        if(t != _latest_device) {
            _latest_device = t;
            changed = true;
        }
    }
    
    // fetch info for ch1 and ch2
    channel_status c;
    for(int index = 0; index < 2; ++index) {
        memset(&c, 0, sizeof(c));
        r = _device->get_channel_status(index, &c);
        if(r == 0) {
            ChannelStatusJson channel;
            QVariantMap t = channel.toVariantMap(c, index);
            if(t != _latest_channel[index]) {
                _latest_channel[index] = t;
                changed = true;
            }
        }
    }
    
    if(changed)
        Q_EMIT onChargerStateChanged();
}

QByteArray iCharger_DeviceController::toJson() const {
    QVariantMap charger;
    charger["key"] = _key;
    charger["info"] = _latest_device;
    QList<QVariant> channels;
    channels << _latest_channel[0];
    channels << _latest_channel[1];
    charger["channels"] = channels;
    return variantMapToJson(charger);
}

