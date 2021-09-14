class Page {
    constructor(connection, ip, pageEsp, status){
      this.connection = connection;
      this.ip = ip;
      this.id = ip.toString().slice(7);
      this.pageEsp = pageEsp;
      this.status = status;
    };

    static heartbeaPage(wsObject) {
      // console.log("oi em cima");
      var current_id = wsObject['_socket']['_peername']['address'].toString().slice(7);
      // console.log("current_id:", current_id);
      global.pages.forEach(function each(page){
        console.log("oi");
        console.log("inside for each", page.id);
        if(current_id == page.id){

          page.status = true;
        }
      });
    };

    static pingPage() {

      global.pages.forEach(function each(page) {
        if (page.status === false) {
          console.log(page.id + " is dead");
          console.log("--------------------------------------------------");
          page.connection.terminate();
          page.taken = false;
          removeItemOnce(global.pages, page);
          return;
        }
    
        page.status = false;
        page.connection.ping(noop);
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

module.exports = Page;