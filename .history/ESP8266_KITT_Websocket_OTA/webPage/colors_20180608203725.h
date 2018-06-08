const char MAIN_page[] PROGMEM = R"=====(
    <!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>AlfaGT</title>
<link rel="icon" href="http://www.alfaromeo.com/favicon.ico" type="image/x-icon" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <script src="lib/jquery-1.6.4.js"></script>
    <script>
        $(document).bind('mobileinit', function() {
            $.mobile.changePage.defaults.changeHash = false;
            $.mobile.hashListeningEnabled = false;
            $.mobile.pushStateEnabled = false;
        });
    </script>
    <script src="lib/jquery.mobile-1.1.0.js"></script>
    <link href="src/css/jquery.mobile.structure-1.1.0.css" rel="stylesheet" />
    <link href="src/css/jquery.mobile.theme-1.1.0.css" rel="stylesheet" />
    <script>
        var ipValue;
        var connection;

        function sendData(watsdoin) {
            var toSend = "RESET";
            connection.send(watsdoin);
        };

        function resetFn() {
            var toSend = "RESET";
            connection.send(toSend);
        };

        function mod() {
            var text = document.getElementById('ip').value;
            ipValue = text;
            connection = new WebSocket(ipValue, ['arduino']);
            console.log(text)
            console.log("IP value changed to:" + ipValue);
        }

        function showValueR(newValue) {
            connection.send("x" + newValue);
        }

        function showValueG(newValue) {
            connection.send("y" + newValue);
        }

        function showValueB(newValue) {
            connection.send("z" + newValue);
        }

        function setRainbowSpeed(newValue) {
            connection.send("t" + newValue);
        }

        function hexToRgb(hex) {
            var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
            return result ? {
                r: parseInt(result[1], 16),
                g: parseInt(result[2], 16),
                b: parseInt(result[3], 16)
            } : null;
        }

        function sendColor(newValue) {
            var RGBColor = hexToRgb(newValue);
            console.log(RGBColor);
            showValueR(Math.round(RGBColor.r / 255 * 1023));
            showValueG(Math.round(RGBColor.g / 255 * 1023));
            showValueB(Math.round(RGBColor.b / 255 * 1023));
        }

        function rainbowFn() {
            var toSend = "RAINBOW";
            connection.send(toSend);
        };
    </script>
</head>

<body>
    <div data-role="page" id="page1">
        <div data-role="header">
            <h1>RGB Slider</h1>
        </div>
        <div data-role="content">
            <div data-role="fieldcontain">
                <label for="text1">WebSocket IP</label>
                <input type="text" id="ip" value="ws://10.0.0.10:81/" onblur='mod()' />
            </div>
            <script>
                mod()
            </script>
            <div data-role="fieldcontain" id="slider1">
                <label for="slider1-range">Red</label>
                <input type="range" id="slider1-range" value="0" min="0" max="1023" step="5" onchange="showValueR(this.value)" data-highlight="true" />
            </div>
            <div data-role="fieldcontain" id="slider2">
                <label for="slider2-range">Green</label>
                <input type="range" id="slider2-range" value="0" min="0" max="1023" onchange="showValueG(this.value)" step="5" data-highlight="true" />
            </div>
            <div data-role="fieldcontain" id="slider3">
                <label for="slider3-range">Blue</label>
                <input type="range" id="slider3-range" value="0" min="0" max="1023" onchange="showValueB(this.value)" step="5" data-highlight="true" />
            </div>
            <div data-role="fieldcontain" id="slider3">
                <label for="slider3-range">Pick Any Color</label>
                <input type="color" id="html5colorpicker" onchange="sendColor(this.value)" value="#ff0000" style="width:85%;">
            </div>
            <div class="ui-grid-b">
                <div class="ui-block-a">
                    <a data-role="button" id="Mode" onclick="sendData(1)" data-inline="true">KITT</a>
                </div>
                <div class="ui-block-b">
                    <a data-role="button" id="Reset" onclick="resetFn()" data-inline="true">Reset</a>
                </div>
                <div class="ui-block-c">
                    <a data-role="button" id="Rainbow" onclick="sendData(7)" data-inline="true">Rainbow</a>
                </div>
                <div class="ui-block-d">
                    <a data-role="button" id="CopMode" onclick="sendData(4)" data-inline="true">CopMode</a>
                </div>
            </div>
            <div data-role="fieldcontain" id="slider3">
                <label for="slider3-range">KITT Speed</label>
                <input type="range" id="slider3-range" value="0" min="10" max="2000" onchange="setRainbowSpeed(this.value)" step="5" data-highlight="true" />
            </div>
            <div data-role="fieldcontain" id="slider3">
                <label for="slider3-range">KITT Delay</label>
                <input type="radio" name="delay" value="10">
                <input type="radio" name="delay" value="30">
                <input type="radio" name="delay" value="60">
                <input type="submit" name="delay" value="send" onclick="setRainbowDelay()">
            </div>
        </div>
        <div data-role="footer">
            <h1>Made by TDAFischer with the majority of the hard work borrowed from Amir Avni</h1>
        </div>
    </div>
</body>

</html>
)=====";