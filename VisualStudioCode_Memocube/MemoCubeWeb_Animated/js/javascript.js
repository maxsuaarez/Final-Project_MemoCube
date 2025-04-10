

    const connection = SimpleWebSerial.setupSerialConnection(
        {
            baudRate: 9600,
            requestAccessOnPageLoad: true,
        }
    );

    async function toggleLED() {
      console.log("Toggling LED...");
        connection.send('led', 1);
        //location.href="second.html";
    }