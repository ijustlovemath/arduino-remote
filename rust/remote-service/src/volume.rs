use actix_web::{HttpResponse, get};
use actix_web::http::header::ContentType;

fn base(serial_command: &str) -> HttpResponse {
    let response = crate::arduino::send("/dev/ttyUSB0", serial_command.as_bytes()).unwrap();


    HttpResponse::Ok()
        .content_type(ContentType::json())
        .json(response)

}

#[get("/volume/up")]
pub async fn up() -> HttpResponse {
    let serial_command = "volume up\n";
    base(&serial_command)
}

#[get("/volume/down")]
pub async fn down() -> HttpResponse {
    let serial_command = "volume down";
    base(&serial_command)
}
