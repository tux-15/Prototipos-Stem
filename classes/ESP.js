var moment = require('moment')

class Esp {
    constructor(connection, id, status, type){
      this.connection = connection;
      this.id = id;
      this.status = status;
      this.taken;
      this.type = type
    };

    static heartbeat(wsObject) {
      var current_id = wsObject['_socket']['_peername']['address'].toString().slice(-3);
      global.esps.forEach(function each(esp){
        if(current_id == esp.id){
          esp.status = true;
        }
      });
    };

    static ping() {

      global.esps.forEach(function each(esp) {
        if (esp.status === false) {
          console.log(moment().format('MMMM Do YYYY, h:mm:ss a'), "|| ", esp.id + " is dead");
          console.log("--------------------------------------------------");
          esp.connection.terminate();
          esp.taken = false;
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