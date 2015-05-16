var router = require('koa-joi-router');
var koa = require('koa');
var Timeline = require('pebble-api');
var timeline = new Timeline();
var token = '---------------------'; 
var app = module.exports = koa();
var router = router();

app.use(router.middleware());
app.listen(8080, function () {
  console.log(arguments);
});

router.route({
  method: 'post',
  path: '/v1/update',
  validate: {
    type: 'json'
  },
  handler: [
    newStatus
  ]
});

function* newStatus() {
  if (!this.request.body) {
    this.status = 500;
    this.body = 'You didn\'t send anything';
    return;
  }
  var body = this.request.body;

  yield new Promise(function(resolve, reject) {

    var pin = new Timeline.Pin({
      id: 'toilet-time',
      time: new Date(),
      duration: 10,
      layout: new Timeline.Pin.Layout({
        type: Timeline.Pin.LayoutType.GENERIC_PIN,
        tinyIcon: Timeline.Pin.Icon.NOTIFICATION_FLAG,
        title: 'Bathroom Status'
      })
    });
    
    timeline.sendUserPin(token, pin, function (err) {
         if (err) {
           reject(err);
         }
        resolve();
      console.log('Pin sent successfully!');
    });

  });

  console.log('%j', this.request.body);
}

