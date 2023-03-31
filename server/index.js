'use strict';

const line = require('@line/bot-sdk');
const express = require('express');

// create LINE SDK config from env variables
const config = {
  channelAccessToken: "",//your own token
  channelSecret: "",//your own secret key
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
    getToggle("toggle-pir","...");//pir board ip
    getToggle("toggle-ldr","...");//ldr board ip
    return client.replyMessage(event.replyToken, payload);
  }
  else if(event.type == "message" && event.message.text == "System Off") {
    const payload = {
      type: "text",
      text: "Deacticated System!",
    }
    getToggle("toggle-pir","...");//pir board ip
    getToggle("toggle-ldr","...");//ldr board ip
    
    return client.replyMessage(event.replyToken, payload);
  }
  else if(event.type == "message" && event.message.text == "Dismiss"){
    const payload = {
      type: "text",
      text: "Dismissed!",
    }
    getToggle("toggle-light","...");//pir board ip

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
