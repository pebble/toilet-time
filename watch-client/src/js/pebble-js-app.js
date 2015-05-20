Pebble.addEventListener("ready",function(e) {                     
  Pebble.timelineSubscribe('toilet-time',function () { 
    console.log('Subscribed to toilet-time');
  }, function (errorString) { 
    console.log('Error subscribing to topic: ' + errorString);
  });
});
