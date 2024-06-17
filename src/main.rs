use std::collections::HashMap;

use dns::dns_header;

mod dns {
    pub mod dns_header;
    pub mod dns_question;
    pub mod dns_record;
}
mod utility {
    pub mod packet_buffer;
    pub mod result_code;
}

fn main() {
    let mut header = dns_header::DNSHeader::new();

    /* DNS records */
    let mut records: HashMap<String, (u8, u8, u8, u8)> = HashMap::new();

    records.insert(String::from("google.com"), (142, 250, 67, 174));

    let (a, b, c, d) = records.get("google.com").unwrap();

    println!("The IP address of google.com is {}.{}.{}.{}", a, b, c, d);
}
