class Page {
    constructor(connection, ip, pageEsp, meta){
      this.connection = connection;
      this.ip = ip;
      this.id = ip.toString().slice(7);
      this.pageEsp = pageEsp;
      this.meta = meta;
    };
  };

module.exports = Page;