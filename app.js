const express = require('express');
const bodyParser = require('body-parser');
const router = express.Router();
const app = express();

const path = __dirname + '/views/';
const port = 80;

app.use(express.static(path));
app.use('/', router);

app.use(express.urlencoded())

router.use(function (req,res,next) {
    next();
});
  
router.get('/', function(req,res){
    res.sendFile(path + 'index.html');
});

app.post('/enviar', function(req,res){
    var msg = req.body.mensaje
    var broker = req.body.broker
    if(broker.search('mqtt://') == -1) {
        broker = 'mqtt://' + broker;
    }
    var topic = req.body.topic
    if(topic.length > 0) {

        var mqtt = require('mqtt')

        var client  = mqtt.connect(broker);
        client.on('connect', function () {
            
            client.publish(topic, msg)
            console.log("Mensaje enviado");
            client.end();
        })
                
        res.sendFile(path + 'index.html');
    }
});
  


app.listen(port, function () {
    console.log('Ejecutando en puerto 80: http://localhost')
})