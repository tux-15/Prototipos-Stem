class Page {
    constructor(connection, ip, status){
      this.connection = connection;
      this.ip = ip;
      // this.status = status
      this.id = ip.toString().slice(7);
    }
  }

module.exports = Page;