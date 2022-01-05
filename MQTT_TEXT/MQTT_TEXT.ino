/*
基本的ESP8266 MQTT示例

 该草图演示了pubsub库的组合功能
 与ESP8266板/库。
 它连接到MQTT服务器，然后：
   - 每两秒向“outTopic”主题发布“hello world”
   - 订阅“inTopic”主题，打印出任何消息
    它接收。 NB  - 它假设收到的有效载荷是非二进制的字符串
   - 如果主题“inTopic”的第一个字符为1，则打开ESP Led，
    否则关掉它
 如果使用阻止丢失连接，它将重新连接到服务器
 重新连接功能。有关如何使用，请参阅'mqtt_reconnect_nonblocking'示例
 在不阻塞主循环的情况下实现相同的结果。

 要安装ESP8266板，（使用Arduino 1.6.4+）：
   - 在“文件 - >首选项 - >其他板卡管理器URL”下添加以下第三方板卡管理器：
      http://arduino.esp8266.com/stable/package_esp8266com_index.json
   - 打开“工具 - >板 - >板管理器”，然后单击ESP8266的安装“
   - 在“工具 - >板”中选择您的ESP8266
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "PokerXie";//你要让板子链接的WiFi的名字
const char* password = "123456789";//该WiFi的密码
const char* mqtt_server = "www.mrxie.xyz";//你的服务器地址

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
   Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}//链接WiFi

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }//串口打印出收到的信息
  Serial.println();

  // 如果收到1作为第一个字符，则打开LED
  if ((char)payload[3] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // 这里他说接受的‘1’就打开灯 
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";//该板子的链接名称
    clientId += String(random(0xffff), HEX);//产生一个随机数字 以免多块板子重名
    //尝试连接
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // 连接后，发布公告......
      client.publish("outTopic", "hello world");//链接成功后 会发布这个主题和语句
      // ......并订阅
      client.subscribe("led");//这个是你让板子订阅的主题（接受该主题的消息）
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // 如果链接失败 等待五分钟重新链接
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // 将BUILTIN_LED引脚初始化为输出
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server,1883);//MQTT默认端口是1883
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);//串口打印，串口调试器可以看到的
    client.publish("outTopic", msg);//接收该主题消息
  }
}
