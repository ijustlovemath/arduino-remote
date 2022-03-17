use actix_web::{App, HttpServer};
use actix_web::middleware;
use std::io;
use std::env;
use env_logger;

//use power;
mod volume;
#[actix_web::main]
async fn main() -> io::Result<()> {
    env::set_var("RUST_LOG", "actix_web=debug,actix_server=info");
    env_logger::init();

    HttpServer::new(|| {
        App::new()
            // enable logger - always register actix-web Logger middleware last
            .wrap(middleware::Logger::default())
            // register HTTP requests handlers
            .service(volume::up)
            .service(volume::down)
          //  .service(power::toggle)
    })
    .bind("0.0.0.0:9090")?
    .run()
    .await
}
