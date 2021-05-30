#include "esphome.h"



class SDMComponent : public PollingComponent {
public:
  SDM sdm = SDM(Serial, 9600, NOT_A_PIN,SERIAL_8N1,false);
  

  Sensor *voltage_sensorAVG = new Sensor();//total mean
  Sensor *voltage_sensorL1 = new Sensor();
  Sensor *voltage_sensorL2 = new Sensor();
  Sensor *voltage_sensorL3 = new Sensor();
  
    
  Sensor *current_sensorSUM = new Sensor();//total sum
  Sensor *current_sensorL1 = new Sensor();
  Sensor *current_sensorL2 = new Sensor();
  Sensor *current_sensorL3 = new Sensor();
  Sensor *current_sensorAVG = new Sensor();

  Sensor *power_sensorSUM = new Sensor(); // Total sum
  Sensor *power_sensorL1 = new Sensor();
  Sensor *power_sensorL2 = new Sensor();
  Sensor *power_sensorL3 = new Sensor();

  Sensor *import_sensorL1 = new Sensor();
  Sensor *import_sensorL2 = new Sensor();
  Sensor *import_sensorL3 = new Sensor();

  Sensor *export_active_sensorSUM = new Sensor();     // export ACTIV ... pretok
  Sensor *export_active_sensorL1 = new Sensor();
  Sensor *export_active_sensorL2 = new Sensor();
  Sensor *export_active_sensorL3 = new Sensor();  


  Sensor *total_energy_sensorL1 = new Sensor();
  Sensor *total_energy_sensorL2 = new Sensor();
  Sensor *total_energy_sensorL3 = new Sensor();  

  Sensor *hz_sensor = new Sensor();         //HZ

  Sensor *va_reactive_sensorSUM = new Sensor();     // REACTIV 
  Sensor *va_reactive_sensorL1 = new Sensor();
  Sensor *va_reactive_sensorL2 = new Sensor();
  Sensor *va_reactive_sensorL3 = new Sensor();  
  Sensor *import_total = new Sensor(); // all kwh sum

  SDMComponent() : PollingComponent(15000) {}

  void setup() override {
    ESP_LOGD("SDM630", "Setup completed");
  }

  void update() override {
    ESP_LOGD("SDM630", "Start reading");

    float vasum = sdm.readVal(SDM630_VOLT_AMPS_REACTIVE_TOTAL); // VA Reactive Energy
    float var1 = sdm.readVal(SDM630_VOLT_AMPS_REACTIVE1); 
    float var2 = sdm.readVal(SDM630_VOLT_AMPS_REACTIVE2); 
    float var3 = sdm.readVal(SDM630_VOLT_AMPS_REACTIVE3); 
    va_reactive_sensorSUM->publish_state(vasum);
    va_reactive_sensorL1->publish_state(var1);
    va_reactive_sensorL2->publish_state(var2);
    va_reactive_sensorL3->publish_state(var3);
  
    float te1 = sdm.readVal(SDM630_TOTAL_ENERGY1); // Total Energy Kwh
    float te2 = sdm.readVal(SDM630_TOTAL_ENERGY2); 
    float te3 = sdm.readVal(SDM630_TOTAL_ENERGY3);
    float timp = sdm.readVal(SDM630_IMPORT_ACTIVE_ENERGY);
    total_energy_sensorL1->publish_state(te1);
    total_energy_sensorL2->publish_state(te2);
    total_energy_sensorL3->publish_state(te3);
    import_total->publish_state(timp);


    float eas = sdm.readVal(SDM630_EXPORT_ACTIVE_ENERGY); // Export Active Energy (pretok)
    float ea1 = sdm.readVal(SDM630_EXPORT1); 
    float ea2 = sdm.readVal(SDM630_EXPORT2); 
    float ea3 = sdm.readVal(SDM630_EXPORT3); 
    export_active_sensorSUM->publish_state(eas);
    export_active_sensorL1->publish_state(ea1);
    export_active_sensorL2->publish_state(ea2);
    export_active_sensorL3->publish_state(ea3);



    float hzf = sdm.readVal(SDM630_FREQUENCY); // HZ
    hz_sensor->publish_state(hzf);

    float voltageAVG = sdm.readVal(SDM630_VOLTAGE_AVERAGE);//voltage   
    float voltage1 = sdm.readVal(SDM630_VOLTAGE1);
    float voltage2 = sdm.readVal(SDM630_VOLTAGE2);
    float voltage3 = sdm.readVal(SDM630_VOLTAGE3);
    ESP_LOGD("SDM630", "Voltages %f %f %f  avg  %f", voltage1, voltage2, voltage3,voltageAVG);
    voltage_sensorAVG->publish_state(voltageAVG);
    voltage_sensorL1->publish_state(voltage1);
    voltage_sensorL2->publish_state(voltage2);
    voltage_sensorL3->publish_state(voltage3);
   
    float currentSUM = sdm.readVal(SDM630_CURRENTSUM);//Current
    float currentL1 = sdm.readVal(SDM630_CURRENT1);
    float currentL2 = sdm.readVal(SDM630_CURRENT2);
    float currentL3 = sdm.readVal(SDM630_CURRENT3);
    float currentAVG = sdm.readVal(SDM630_CURRENT_AVERAGE );
    current_sensorSUM->publish_state(currentSUM);
    current_sensorL1->publish_state(currentL1);
    current_sensorL2->publish_state(currentL2);
    current_sensorL3->publish_state(currentL3);
    current_sensorAVG->publish_state(currentAVG);


    float powerSUM = sdm.readVal(SDM630_POWERTOTAL);//power
    float power1 = sdm.readVal(SDM630_POWER1);
    float power2 = sdm.readVal(SDM630_POWER2);
    float power3 = sdm.readVal(SDM630_POWER3);
    power_sensorSUM->publish_state(powerSUM);
    power_sensorL1->publish_state(power1);    
    power_sensorL2->publish_state(power2);
    power_sensorL3->publish_state(power3);    

    float import1 = sdm.readVal(SDM630_IMPORT1);//import 
    float import2 = sdm.readVal(SDM630_IMPORT2);
    float import3 = sdm.readVal(SDM630_IMPORT3);
    ESP_LOGD("SDM630", "Imports %f %f %f", import1, import2, import3);
    import_sensorL1->publish_state(import1);
    import_sensorL2->publish_state(import2);
    import_sensorL3->publish_state(import3);

    ESP_LOGD("SDM630", "End reading");
  }
};
/*
class SDM120Component : public PollingComponent {
public:
  SDM sdm = SDM(Serial , 9600, NOT_A_PIN, SERIAL_8N1, false);

  Sensor *voltage_sensor = new Sensor();

  Sensor *current_sensor = new Sensor();

  Sensor *power_sensor = new Sensor(); 
  Sensor *ACTIVE_APPARENT_POWER = new Sensor();
  Sensor *REACTIVE_APPARENT_POWER = new Sensor();
  Sensor *POWER_FACTOR = new Sensor();
  Sensor *FREQUENCY = new Sensor();
  Sensor *IMPORT_ACTIVE_ENERGY = new Sensor();
  Sensor *EXPORT_ACTIVE_ENERGY = new Sensor(); //pretok
  Sensor *TOTAL_ACTIVE_ENERGY = new Sensor();

  SDM120Component() : PollingComponent(15000) {}

  void setup() override {
    ESP_LOGD("SDM120", "Setup completed");
  }


  void update() override {
    ESP_LOGD("SDM120", "Start reading");
  
    float voltage = sdm.readVal(SDM120C_VOLTAGE); //voltage  
    voltage_sensor->publish_state(voltage);
    float current = sdm.readVal(SDM120C_CURRENT);//Current
    current_sensor->publish_state(current);
    float power = sdm.readVal(SDM120C_POWER);//power
    power_sensor->publish_state(power);
    float aap = sdm.readVal(SDM120C_ACTIVE_APPARENT_POWER);//SDM120C_ACTIVE_APPARENT_POWER  
    ACTIVE_APPARENT_POWER->publish_state(aap);
    float rap = sdm.readVal(SDM120C_REACTIVE_APPARENT_POWER);//SDM120C_REACTIVE_APPARENT_POWER
    REACTIVE_APPARENT_POWER->publish_state(rap);
    float pf = sdm.readVal(SDM120C_POWER_FACTOR);//SDM120C_POWER_FACTOR
    POWER_FACTOR->publish_state(pf);
    float fre = sdm.readVal(SDM120C_FREQUENCY);//SDM120C_FREQUENCY
    FREQUENCY->publish_state(fre); 
    float iae = sdm.readVal(SDM120C_IMPORT_ACTIVE_ENERGY);//SDM120C_IMPORT_ACTIVE_ENERGY   
    IMPORT_ACTIVE_ENERGY->publish_state(iae);
    float eae = sdm.readVal(SDM120C_EXPORT_ACTIVE_ENERGY);//SDM120C_EXPORT_ACTIVE_ENERGY
    EXPORT_ACTIVE_ENERGY->publish_state(eae);
    float tae = sdm.readVal(SDM120C_TOTAL_ACTIVE_ENERGY);//SDM120C_TOTAL_ACTIVE_ENERGY
    TOTAL_ACTIVE_ENERGY->publish_state(tae);
    ESP_LOGD("SDM120", "End reading");
  }
};
*/