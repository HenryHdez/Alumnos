var assert = require("assert"),
        brain = require("../../lib/brain");
console.log('Running asynchronous oracle function for XOR...');
var net = new brain.NeuralNetwork({hiddenLayers: [80]});
net.train([
    {input: [0, 0], output: [0.0]}
], {errorThresh: .05, iterations: 1, log: false, logPeriod: 20, learningRate: .2});
var done;
var err = 1;
var i = 0;
var inputs = [[0, 0], [0, 1], [1, 0], [1, 1]];
var train = function () {
    net.trainFunction(inputs[i], function (outputs, cb) {
        //This is the oracle function. It will tell the neural network
        //how close it is for each given input.
        
        process.nextTick(function () {
            var input = inputs[i];
            cb([(input[0] ^ input[1]) - outputs[0]]);
        });
    }, .2,function(error){
        err+=error;
        i++;
        if(i<inputs.length) {
            train();
        }else {
            i = 0;
            if(err>.05) {
                err = 0;
                train();
            }else {
                done();
            }
        }
    });
};
train();
console.log('Training is in progress.....');

done = function () {

    console.log('Training has completed within error margin of: '+err);
    for (var i = 0; i < inputs.length; i++) {
        var input = inputs[i];
        console.log(input[0] + ' ^ ' + input[1] + ' == ' + (net.run(input) > .5) * 1);
    }
};