var router = require('koa-joi-router');
var logger = require('koa-logger')
var koa = require('koa');
var Timeline = require('pebble-api');
var timeline = new Timeline({ apiKey: process.env.API_KEY });
var app = module.exports = koa();
var router = router();

app.use(logger());
app.use(router.middleware());
app.listen(8080);

router.route({
  method: 'post',
  path: '/v1/update',
  validate: {
    type: 'json'
  },
  handler: [ newStatus ]
});

function* newStatus() {
  if (!this.request.body) {
    this.status = 500;
    this.body = 'You didn\'t send anything';
    return;
  }
  var body = this.request.body;

  var bathroomStatus;
  if (body.locked == 1){
    bathroomStatus = 'Occupied';
  } else {
    bathroomStatus = 'Vacant';
  }

  yield new Promise(function(resolve, reject) {

    var pin = new Timeline.Pin({
      id: 'toilet-time',
      time: new Date(),
      duration: 10,
      layout: new Timeline.Pin.Layout({
        type: Timeline.Pin.LayoutType.GENERIC_PIN,
        tinyIcon: Timeline.Pin.Icon.NOTIFICATION_FLAG,
        title: 'Bathroom ' + bathroomStatus
      })
    });
    
    timeline.sendSharedPin(['toilet-time'], pin, function (err) {
      if (err) { reject(err) }
      resolve();
    });

  });

  this.body = 'success';
}
