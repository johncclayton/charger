#include <QDebug>
#include <QThread>
#include <QVariantMap>

#include "icharger_controller.h"
#include "icharger/icharger_message_keys.h"
#include "usb/icharger_data.h"
#include "json_helper.h"

struct DeviceOnlyJson : public device_only {
    QVariantMap toVariantMap() const {
        QVariantMap data;
        
        data[STR_DEVICE_ONLY_ID] = device_id.value;
        data[STR_DEVICE_ONLY_SERIAL_NUMBER] = QString::fromLatin1((const char*)device_sn, 12).trimmed();
        data[STR_DEVICE_ONLY_HW_VERSION] = (float)hw_version.value / 10;
        data[STR_DEVICE_ONLY_SW_VERSION] = (float)sw_version.value / 10;
        data[STR_DEVICE_ONLY_CH1_STATUS] = ch1_status.value;
        data[STR_DEVICE_ONLY_CH2_STATUS] = ch2_status.value;
        
        return data;
    }
};

struct ChannelStatusJson : public channel_status {
    QVariantMap toVariantMap(int channel) const {
        QVariantMap data;
        
        data[STR_CHANNEL_STATUS_CHANNEL_NUM] = channel;
        data[STR_CHANNEL_STATUS_OUTPUT_POWER] = quint32(output_power.value);
        data[STR_CHANNEL_STATUS_OUTPUT_CURRENT] = output_current.value;
        data[STR_CHANNEL_STATUS_OUTPUT_VOLTAGE] = output_voltage.value / 1000.0;
        data[STR_CHANNEL_STATUS_OUTPUT_CAPACITY] = quint32(output_capacity.value);
        
        data[STR_CHANNEL_STATUS_INPUT_VOLTAGE] = input_voltage.value / 1000.0;
        
        data[STR_CHANNEL_STATUS_TEMP_INTERNAL] = temp_internal.value / 10.0;
        data[STR_CHANNEL_STATUS_TEMP_EXTERNAL] = temp_external.value / 10.0;
        
        QVariantList cells;
        for(int index = 0; index < MAX_CELLS; ++index) {
            QVariantMap cell;
            cell[STR_CHANNEL_STATUS_CELL_VOLTAGE] = cell_voltage[index];
            cell[STR_CHANNEL_STATUS_CELL_BALANCE_STATUS] = balance_status[index];
            cell[STR_CHANNEL_STATUS_CELL_RESISTANCE] = cell_resistance[index];
            cells << cell;
        }    
        
        data[STR_CHANNEL_STATUS_CELLS] = cells;
        
        data[STR_CHANNEL_STATUS_TOTAL_RESISTANCE] = total_resistance;
        data[STR_CHANNEL_STATUS_LINE_INTERNAL_RESISTANCE] = line_internal_resistance;
        data[STR_CHANNEL_STATUS_CYCLE_COUNT] = cycle_count;
        data[STR_CHANNEL_STATUS_CONTROL_STATUS] = control_status;
        data[STR_CHANNEL_STATUS_RUN_STATUS] = run_status;
        data[STR_CHANNEL_STATUS_RUN_ERROR] = run_error;
        data[STR_CHANNEL_STATUS_DIALOG_BOX_ID] = dialog_box_id;
        
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
    DeviceOnlyJson device;
    int r = _device->get_device_only(&device);
    if(r == 0) {
        QVariantMap t = device.toVariantMap();
        if(t != _latest_device) {
            _latest_device = t;
            changed = true;
        }
    }
    
    // fetch info for ch1 and ch2
    ChannelStatusJson channel[2];
    for(int index = 0; index < 2; ++index) {
        r = _device->get_channel_status(index, &channel[index]);
        if(r == 0) {
            QVariantMap t = channel[index].toVariantMap(index);
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
    charger["device"] = _latest_device;
    QList<QVariant> channels;
    channels << _latest_channel[0];
    channels << _latest_channel[1];
    charger["channels"] = channels;
    return variantMapToJson(charger);
}

