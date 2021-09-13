class Esp {
    constructor(connection, ip, status){
      this.connection = connection;
      this.id = ip.toString().slice(17);
      this.status = status

    };

    static heartbeat(wsObject) {
      var current_ip = wsObject['_socket']['_peername']['address'];
      global.esps.forEach(function each(esp){
        if(current_ip == esp.ip){
          esp.status = true;
        }
      });
    };

    static ping() {

      global.esps.forEach(function each(esp) {
        if (esp.status === false) {
          console.log(esp.id + " is dead");
          console.log("--------------------------------------------------");
          esp.connection.terminate();
          removeItemOnce(global.esps, esp);
          return;
        }
    
        esp.status = false;
        esp.connection.ping(noop);
      });
    };

  };

function noop() {};  

function removeItemOnce(arr, value) {
  var index = arr.indexOf(value);
  if (index > -1) {
    arr.splice(index, 1);
  };
  return;
};

module.exports = Esp;