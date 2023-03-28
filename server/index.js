'use strict';

const line = require('@line/bot-sdk');
const express = require('express');

// create LINE SDK config from env variables
const config = {
  channelAccessToken: "COfu9/s2C0uKvsOkkgUmyI44TTlNPVv6W1f7lqgJGWEe7L6ziUIn4njxyKIb29N4HlxlYrcu4Yiti2Bq1QFt2rXHnzmlS0eApTj7Ql9ptJHjj+R4ut2VqrN+/aKg3Gr0VmGlXRYPwq5qzuqIRd4IrAdB04t89/1O/w1cDnyilFU=",
  channelSecret: "8556acf116c5a6777d14d7263c5b5dfb",
};

// create LINE SDK client
const client = new line.Client(config);

// create Express app
const app = express();

// register a webhook handler with middleware
app.post('/callback', line.middleware(config), (req, res) => {
  Promise
    .all(req.body.events.map(handleEvent))
    .then((result) => res.json(result))
    .catch((err) => {
      console.error(err);
      res.status(500).end();
    });
});

// event handler
function handleEvent(event) {
  console.log(event.message.text)
  if (event.type !== 'message' && event.message.type !== 'text') {
    // ignore non-text-message event
    return Promise.resolve(null);
  }else if(event.type == "message" && event.message.text == "System On") {
    const payload = {
      type: "text",
      text: "Acticated System!",
    }
    getToggle("toggle-pir","172.20.10.11");
    getToggle("toggle-ldr","172.20.10.4");
    return client.replyMessage(event.replyToken, payload);
  }
  else if(event.type == "message" && event.message.text == "System Off") {
    const payload = {
      type: "text",
      text: "Deacticated System!",
    }
    getToggle("toggle-pir","172.20.10.11");
    getToggle("toggle-ldr","172.20.10.4");
    
    return client.replyMessage(event.replyToken, payload);
  }
  else if(event.type == "message" && event.message.text == "Dismiss"){
    const payload = {
      type: "text",
      text: "Dismissed!",
    }
    getToggle("toggle-light","172.20.10.11");

    return client.replyMessage(event.replyToken, payload);
    }
    // fake pir
  else if(event.type == "message" && event.message.text == "pir1"){
    const payload = {
      type: "text",
      text: "pir1",
    }
    getToggle("toggle-pir1","172.20.10.11");

    return client.replyMessage(event.replyToken, payload);
    }
  else if(event.type == "message" && event.message.text == "pir2"){
    const payload = {
      type: "text",
      text: "pir2",
    }
    getToggle("toggle-pir2","172.20.10.11");

    return client.replyMessage(event.replyToken, payload);
    }
  else if(event.type == "message" && event.message.text == "pir3"){
    const payload = {
      type: "text",
      text: "pir3",
    }
    getToggle("toggle-pir3","172.20.10.11");

    return client.replyMessage(event.replyToken, payload);
    }
  else if(event.type == "message" && event.message.text == "off"){
    const payload = {
      type: "text",
      text: "off",
    }
    getToggle("toggle-off","172.20.10.11");

    return client.replyMessage(event.replyToken, payload);
    }
}
// listen on port
const port = process.env.PORT || 3000;
app.listen(port, () => {
  console.log(`listening on ${port}`);
});


function getToggle(str,ip){
    // send message to ESP32
    const axios = require('axios');
    // Define the IP address and port of the ESP32
    const ipAddress = ip;
    // e8:68:e7:22:b8:e0 Laser
    // 3c:61:5:3:ae:80 Temp
    // e8:db:84:0:f3:1c Pir
    const port = '80';
    // Define the endpoint to toggle the LED
    const toggleLedEndpoint = `http://${ipAddress}:${port}/${str}`;

    // Make a GET request to the endpoint to toggle the LED
    axios.get(toggleLedEndpoint, { timeout: 5000 })
      .then(response => {
        console.log(response.data);
      })
      .catch(error => {
        console.log(error);
      });
}
