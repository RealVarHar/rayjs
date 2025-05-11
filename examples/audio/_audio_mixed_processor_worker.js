//This is a separate thread dedicated to audio
import * as os from 'qjs:os';
import * as rl from 'rayjs:raylib';
{
    var exponent = 1;                 // Audio exponentiation value
    var averageVolume = new Float32Array(400);   // Average volume history
    function ProcessAudio(buffer, frames){
        let samples = buffer;   // Samples internally stored as <float>s
        let average = 0;               // Temporary average volume

        for (let frame = 0; frame < frames; frame++){
            let left = samples[frame * 2 + 0], right = samples[frame * 2 + 1];

            left = Math.pow(Math.abs(left), exponent) * ( (left < 0)? -1 : 1 );
            right = Math.pow(Math.abs(right), exponent) * ( (right < 0)? -1 : 1 );

            average += Math.abs(left) / frames;   // accumulating average volume
            average += Math.abs(right) / frames;
        }

        // Moving history to the left
        for (let j = 0; j < 399; j++) averageVolume[j] = averageVolume[j + 1];

        averageVolume[399] = average;         // Adding last average value
    }

    rl.AttachAudioMixedProcessor("ProcessAudio");
    var parent = os.Worker.parent;
    function handle_msg(e) {
        if(e.data===0){
            rl.DetachAudioMixedProcessor("ProcessAudio");  // Disconnect audio processor
            parent.postMessage(0);
        }else if(typeof(e.data)=='object'){
            if(e.data[0]=="ProcessAudio") {
                ProcessAudio(e.data[1], e.data[2]);
            }
            return true;
        }else if(typeof(e.data)=='number'){
            exponent=e.data;
            parent.postMessage(averageVolume);
        }
    }
    parent.onmessage = handle_msg;
}