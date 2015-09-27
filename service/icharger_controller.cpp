#include <QVariantMap>
#include <serializer.h>

#include "icharger_controller.h"
#include "usb/icharger_data.h"

QByteArray DeviceOnlyJson::toJson() const {
    QVariantMap data;
    
    data["id"] = device_id.value;
    data["sn"] = QString::fromLatin1((const char*)device_sn, 12).trimmed();
    data["sw_ver"] = (float)hw_version.value / 10;
    data["sw_ver"] = (float)sw_version.value / 10;
    data["ch1_state"] = ch1_status.value;
    data["ch2_state"] = ch2_status.value;
    
    bool ok;
    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(data, &ok);
    if(ok)    
        return json;
    
    return QByteArray();
}

/*
    register32 timestamp;
    register32 output_power;
    register16 output_current;
    register16 input_voltage;
    register16 output_voltage;
    register32 output_capacity;
    
    register16 temp_internal;
    register16 temp_external;
    
    u16 cell_voltage[MAX_CELLS];
    u8 balance_status[MAX_CELLS];
    u16 cell_resistance[MAX_CELLS];
    u16 total_resistance;
    
    u16 line_internal_resistance;
    u16 cycle_count;	
    u16 control_status;
    u16 run_status;
    u16 run_error;
    u16 dialog_box_id;

*/
QByteArray ChannelStatusJson::toJson(int channel) const {
    QVariantMap data;

    data["channel"] = channel;
    data["output_power"] = quint32(output_power.value);
    data["output_current"] = output_current.value;
    data["input_voltage"] = input_voltage.value;
    data["output_voltage"] = output_voltage.value;
    data["output_capacity"] = quint32(output_capacity.value);
    data["temp_internal"] = temp_internal.value;
    data["temp_external"] = temp_external.value;
    
    for(int index = 0; index < MAX_CELLS; ++index) {
            
    }    
    
    bool ok;
    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(data, &ok);
    if(ok)    
        return json;
    
    return QByteArray();
}

iCharger_DeviceController::iCharger_DeviceController(Publisher_ptr pub, icharger_usb_ptr p, QObject *parent) : 
    QObject(parent), _pub(pub), _device(p)
{
    // query status of every bloody thing every second
    startTimer(500 /* ms */);
}

void iCharger_DeviceController::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    
    // fetch device status and publish on the bus
    DeviceOnlyJson device;
    int r = _device->get_device_only(&device);
    if(r == 0) {
        // consert to JSON and make the units sane - then publish
        QByteArray device_json = device.toJson();
        if(_latest_device_json != device_json) {
            _latest_device_json = device_json;
            publish_device_json();
        }
    }
    
    // fetch info for ch1 and ch2
    ChannelStatusJson channel[2];
    for(int index = 0; index < 2; ++index) {
        r = _device->get_channel_status(index, &channel[index]);
        if(r == 0) {
            QByteArray data = channel[index].toJson(index);
            if(data != _latest_channel_json[index]) {
                _latest_channel_json[index] = data;
                publish_channel_json(index);
            }
        }
    }
}

void iCharger_DeviceController::publish_device_json() {
    _pub->publishOnTopic(QString::fromLatin1("icharger/device"), _latest_device_json);
}

void iCharger_DeviceController::publish_channel_json(int index) {
    _pub->publishOnTopic(QString::fromLatin1("icharger/channel/%d").arg(index + 1), _latest_channel_json[index]);
}
