class Page {
    constructor(connection, ip, pageEsp, status){
      this.connection = connection;
      this.ip = ip;
      this.id = ip.toString().slice(7);
      this.pageEsp = pageEsp;
      this.status = status;
    };

    static heartbeaPage(wsObject) {

      var current_id = wsObject['_socket']['_peername']['address'].toString().slice(7);

      global.pages.forEach(function each(page){
        if(current_id == page.id) {page.status = true;};
      });
    };

    static pingPage() {

      global.pages.forEach(function each(page) {
        if (page.status === false) {
          console.log(page.id + " is dead");
          console.log("--------------------------------------------------");
          page.connection.terminate();
          // page.taken = false;

          global.esps.forEach(esp => {
            if (esp.id == page.pageEsp){
              console.log("ESP", esp.id, "is available")
              esp.taken = false;
              global.rooms.forEach(room => {
                if (room["espConnection"] == esp.connection){
                  removeItemOnce(global.rooms, room);
                  console.log(global.rooms);
                }
              })
            }
          });

          //console.log("hm ", global.esps.id.indexOf(page.pageEsp));
          removeItemOnce(global.pages, page);
          return;
        };
    
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