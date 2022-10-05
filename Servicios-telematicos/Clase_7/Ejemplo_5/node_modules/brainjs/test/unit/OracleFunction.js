var assert = require("assert"),
    brain = require("../../lib/brain");
console.log('Running oracle function for XOR...');
var net = new brain.NeuralNetwork({hiddenLayers:[80]});
net.train([
    {input:[0,0],output:[0.0]}
],{errorThresh:.05,iterations:1,log:false,logPeriod:20,learningRate:.2});

var err = 1;
var inputs = [[0,0],[0,1],[1,0],[1,1]];
while(err>.05) {
    err = 0;
    for(var i = 0;i<inputs.length;i++) {
        err += net.trainFunction(inputs[i],function(outputs){
            //This is the oracle function. It will tell the neural network
            //how close it is for each given input.
            var input = inputs[i];
            return [(input[0] ^ input[1])-outputs[0]];
        },.2);
    }
}

    console.log(err);

for(var i = 0;i<inputs.length;i++) {
    var input = inputs[i];
    console.log(input[0]+' ^ '+input[1]+' == '+(net.run(input) > .5)*1);
}