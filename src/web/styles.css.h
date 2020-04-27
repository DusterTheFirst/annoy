R"CSS(
/* Help the css formatter come to grips */
.dummy {}

input[type=range] {
    direction: rtl;
    -webkit-appearance: none;
    appearance: none;

    width: 100%;
    height: 25px;
    background: #80808080;
    outline: none;
    border-radius: 5px;
}

input[type=range]::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;

    width: 20px;
    height: 30px;
    background: #101010;
    cursor: pointer;
    border: 1px solid #404040;
}

input[type=range]::-moz-range-thumb {
    width: 20px;
    height: 30px;
    background: #101010;
    cursor: pointer;
    border: 1px solid #404040;
}

input[type=color] {
    background: none;
    border: none;
}

label {
    display: block;
}

html,
body {
    margin: 0;
    background: black;
    color: white;
}

body {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    text-align: center;
}

.defcon {
    text-align: center;
    padding: 10px 20px;
    margin: 10px;
    color: #000000;
}

.rgb {
    text-align: center;
    padding: 10px 20px;
    margin: 10px;
}
.rgb label {
    margin-top: 5px;
}
)CSS"