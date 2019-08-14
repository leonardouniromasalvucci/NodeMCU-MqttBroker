package edu.softeng.mqttpub;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class Server {    

    public static void main(String[] args) {       

            String topic        = "MQTT Examples";
            int qos             = 2;
            String broker       = "tcp://127.0.0.1:1883";
            String clientId     = "JavaSample2";
            MemoryPersistence persistence = new MemoryPersistence();          



            try {             

                MqttClient sampleClient = new MqttClient(broker, clientId, persistence);
                MqttConnectOptions connOpts = new MqttConnectOptions();
                //connOpts.setCleanSession(true);
                System.out.println("Connecting to broker: "+broker);
               // sampleClient.connect(connOpts);
                System.out.println("Connected");
             

                sampleClient.setCallback(new MqttCallback() {
                    public void connectionLost(Throwable cause) {
                        System.out.println("lostr"+cause.toString());
                    }

                    public void messageArrived(String topic, MqttMessage message) throws Exception {
                          System.out.println("Message: " + message);
                    }

                    public void deliveryComplete(IMqttDeliveryToken token) {
                         System.out.println("delivery");
                    }
                });
                
                sampleClient.connect(connOpts);
                sampleClient.subscribe(topic);                

            } catch(MqttException me) {

                System.out.println("reason "+me.getReasonCode());
                System.out.println("msg "+me.getMessage());
                System.out.println("loc "+me.getLocalizedMessage());
                System.out.println("cause "+me.getCause());
                System.out.println("excep "+me);
                me.printStackTrace();
            }
    }   
}

