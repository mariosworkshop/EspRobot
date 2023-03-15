const SERVO_COUNT = 16;
const DEFAULT_SLIDER_VALUE = 90;
const UNUSED_SLIDERS = 6;
const MAX_VALUE = 180;

let slider_to_move = [];
let servos_pos = [SERVO_COUNT];
let servo_reverse = [SERVO_COUNT];
let rev_btn_state = [SERVO_COUNT];

function print_servos(){
    document.write('<div style="width: 400px; display: inline-block; margin-left: 50px">');

    for (let i = SERVO_COUNT / 2 - 1; i >= 0; i--) {
        document.write('<div style="margin-top: 20px;">');
        document.write('<input type="checkbox" id="chckbx'+ i +'" style="float: left; margin-right: 30px; margin-top: 3px" onclick="getCheckedCheckBoxes()">');
        document.write('<input type="range" class="form-range" id="servo'+ i +'" max="180" min="0" step="2" style="float: left;" onchange="updateValueOneServo('+ i +'); moveSliders('+ i +'); send_data()" oninput="updateValueOneServo('+ i +'); moveSliders('+ i +'); send_data()">');
        document.write('<button type="button" style="float: left; margin-left: 20px" id="revbtn'+ i +'" class="btn btn-warning btn-sm" onclick="reverseValue('+ i +')"><b>R</b></button>');
        document.write('<p id="value'+ i +'"style="margin-top: auto;margin-bottom: auto; font-weight: bold;"></p>');
        document.write('</div>');
    }

    document.write('</div>');
    document.write('<div style="width: 400px; display: inline-block;">');

    for (let i = SERVO_COUNT / 2; i < SERVO_COUNT; i++) {
        document.write('<div style="margin-top: 20px;">');
        document.write('<input type="checkbox" id="chckbx'+ i +'" style="float: left; margin-right: 30px; margin-top: 3px" onclick="getCheckedCheckBoxes()">');
        document.write('<input type="range" class="form-range" id="servo'+ i +'" max="180" min="0" step="2" style="float: left;" onchange="updateValueOneServo('+ i +'); moveSliders('+ i +'); send_data()" oninput="updateValueOneServo('+ i +'); moveSliders('+ i +'); send_data()">');
        document.write('<button type="button" style="float: left; margin-left: 20px" id="revbtn'+ i +'" class="btn btn-warning btn-sm" onclick="reverseValue('+ i +')"><b>R</b></button>');
        document.write('<p id="value'+ i +'"style="margin-top: auto;margin-bottom: auto; font-weight: bold;"></p>');
        document.write('</div>');
    }

    document.write('</div>');
}

initializeReverse();

function initializeReverse(){
    for (let i = 0; i < SERVO_COUNT; i++) {
        servo_reverse[i] = false;
    }
}

function reverseValue(pos){
    servo_reverse[pos] = !servo_reverse[pos];
    if(servo_reverse[pos] == true){
        document.getElementById("revbtn" + pos).className = "btn btn-danger btn-sm";
        document.getElementById("value" + pos).innerHTML = Math.abs(document.getElementById("servo" + pos).value - MAX_VALUE);
    }else{
        document.getElementById("revbtn" + pos).className = "btn btn-warning btn-sm";
        document.getElementById("value" + pos).innerHTML = document.getElementById("servo" + pos).value;
    }
}

function resetReverse(){
    for (let i = 0; i < SERVO_COUNT; i++) {
        servo_reverse[i] = false;
        document.getElementById("revbtn" + i).className = "btn btn-warning btn-sm";
    }
}

function disableElements(){
    for(let i = SERVO_COUNT / 2 - UNUSED_SLIDERS / 2; i < SERVO_COUNT / 2; i++){
        document.getElementById("servo" + i).disabled = true;
        document.getElementById("chckbx" + i).disabled = true;
        document.getElementById("revbtn" + i).disabled = true;
    }
    for(let i = SERVO_COUNT / 2; i < SERVO_COUNT / 2 + UNUSED_SLIDERS / 2; i++){
        document.getElementById("servo" + i).disabled = true;
        document.getElementById("chckbx" + i).disabled = true;
        document.getElementById("revbtn" + i).disabled = true;
    }
}

function updateValue(){
    let position = 0;

    for (let i = 0; i < SERVO_COUNT; i++) {
        if(servo_reverse[i] == true){
            position = document.getElementById("servo"+ i +"").value;
            document.getElementById("value"+ i).innerHTML = Math.abs(position - MAX_VALUE);
            console.log("tu som");
        }else{
            document.getElementById("value"+ i).innerHTML = document.getElementById("servo"+ i +"").value;
        }
    }
}

function updateValueOneServo(servo_i){
    let position = 0;

    if(servo_reverse[servo_i] == true){
        position = document.getElementById("servo"+ servo_i +"").value;
        document.getElementById("value"+ servo_i).innerHTML = Math.abs(position - MAX_VALUE);
        console.log("tu som");
    }else{
        document.getElementById("value"+ servo_i).innerHTML = document.getElementById("servo"+ servo_i +"").value;
    }
}

function sendLastPosition(){
    if(document.getElementById("savedPoses").value != ""){
        let servos = document.getElementById("savedPoses").value;
        servos = servos.split('\n');
        servos = servos.slice(-1);
        servos = servos[0].split(',');
        console.log(servos);
    
        for(let i = 0; i < SERVO_COUNT; i++){
            
            rev_btn_state = (document.getElementById("reverse_btn_state").value).split(',');

            if(rev_btn_state[i] == 1){
                //document.getElementById("revbtn" + i).className = "btn btn-danger btn-sm";
                if(document.getElementById("revbtn" + i).className != "btn btn-danger btn-sm"){
                    document.getElementById("revbtn" + i).click();
                }
                document.getElementById("servo" + i).value = Math.abs(servos[i] - MAX_VALUE);
            }else{
                //document.getElementById("revbtn" + i).className = "btn btn-warning btn-sm";
                if(document.getElementById("revbtn" + i).className != "btn btn-warning btn-sm"){
                    document.getElementById("revbtn" + i).click();
                }
                document.getElementById("servo" + i).value = servos[i];
            }
            document.getElementById("value" + i).innerHTML = servos[i];
        }

        send_data();
    }
}

function resetCheckBoxes(){
    for (let i = 0; i < SERVO_COUNT; i++) {
        document.getElementById("chckbx" + i).checked = false;
    }
    slider_to_move = null;
}

function resetSliders(){
    for (let i = 0; i < SERVO_COUNT; i++) {
        document.getElementById("servo" + i).value = DEFAULT_SLIDER_VALUE;
        document.getElementById("value"+ i).innerHTML = DEFAULT_SLIDER_VALUE;
    }
    send_data();
}

function savePoses(){
    let text_to_write;

    for(let i = 0; i < SERVO_COUNT; i++){
        servos_pos[i] = document.getElementById("value" + i).innerHTML;

        if(document.getElementById("revbtn" + i).className == "btn btn-danger btn-sm"){
            rev_btn_state[i] = 1;
        }else{
            rev_btn_state[i] = 0;
        }
    }

    document.getElementById("reverse_btn_state").value = rev_btn_state;

    if(document.getElementById("savedPoses").value == ""){
        text_to_write = servos_pos;
    }else{
        text_to_write = document.getElementById("savedPoses").value + "\n" + servos_pos;
    }
    document.getElementById("savedPoses").value = text_to_write;
}

function clearPoses(){
    document.getElementById("savedPoses").value = "";
    document.getElementById("reverse_btn_state").value = "";
}

function getCheckedCheckBoxes(){
    const sliders_move = [];

    for (let i = 0; i < SERVO_COUNT; i++) {
        if(document.getElementById("chckbx" + i).checked == true){
            sliders_move.push(i);
        }
    }
    slider_to_move = sliders_move;
    console.log(slider_to_move);
}

function moveSliders(servo_i){
    if(slider_to_move != null){
        slider_to_move.forEach(element => {
            if(element == servo_i){
            }else{
                if(slider_to_move.includes(servo_i)){
                    document.getElementById("servo" + element).value = document.getElementById("servo" + servo_i).value;
                    updateValue();
                    send_data();
                }
            }
        });
    }
}

function send_data(){
    var xhhtp = new XMLHttpRequest();
    let counter = 0;
    let servo_arr;

    xhhtp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
            console.log(this.responseText);
        }
    };

    for(let i = 0; i < SERVO_COUNT; i++){
        servos_pos[counter] = document.getElementById("value" + i).innerHTML;
        counter++;
    }
    console.log(servos_pos);

    xhhtp.open("GET", "setPOS?servoPOS=" + servos_pos, true);
    xhhtp.send();
}

function download() {
    const file = new File([document.getElementById("savedPoses").value], 'servos_poses.txt', {
        type: 'text/plain',
    });

    const link = document.createElement('a');
    const url = URL.createObjectURL(file);
  
    link.href = url;
    link.download = file.name;
    document.body.appendChild(link);
    link.click();
  
    document.body.removeChild(link);
    window.URL.revokeObjectURL(url);
  }