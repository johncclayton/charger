#include <QDebug>
#include <QThread>
#include <QVariantMap>

#include "icharger_controller.h"
#include "icharger_message_keys.h"
#include "usb/icharger_data.h"
#include "charger_state.h"
#include "json_helper.h"

struct DeviceOnlyJson : public device_only {
    void writeToChargerState(ChargerState& state);
};

struct ChannelStatusJson : public channel_status {
    void writeToChargerState(ChargerState& state, int channel);
};

void DeviceOnlyJson::writeToChargerState(ChargerState& state) const {
    state.info().setSerialNumber(QString::fromLatin1((const char*)device_sn, 12).trimmed());
    state.info().setSoftwareVersion((float)sw_version.value / 10);
    state.info().setHardwareVersion((float)hw_version.value / 10);
    state.info().setCh1Status(ch1_status.value);
    state.info().setCh2Status(ch2_status.value);
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

void ChannelStatusJson::writeToChargerState(ChargerState& state, int channel) const {
    ChannelStatus& ch = channel == 0 ? state.ch1() : state.ch2();
    ch.setChannel(channel);
/*    
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
  */  
}

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
    // fetch device status and publish on the bus
    DeviceOnlyJson device;
    int r = _device->get_device_only(&device);
    if(r == 0) 
        device.writeToChargerState(_state);
    
    // fetch info for ch1 and ch2
    ChannelStatusJson channel[2];
    for(int index = 0; index < 2; ++index) {
        r = _device->get_channel_status(index, &channel[index]);
        if(r == 0) 
            channel[index].writeToChargerState(_state, index);
    }
    
    Q_EMIT onChargerStateChanged();
}

QByteArray iCharger_DeviceController::toJson() const {
    return variantMapToJson(_state.toVariantMap());
}

