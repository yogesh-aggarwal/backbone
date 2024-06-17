use std::collections::HashMap;

use dns::dns_header;

mod dns {
    pub mod dns_header;
    pub mod dns_question;
    pub mod dns_record;

    pub mod core {
        pub mod packet_buffer;
        pub mod query_type;
    }
}

mod utility {
    pub mod result;
    pub mod result_code;
}

fn main() {
    /* DNS records */
    let mut records: HashMap<String, (u8, u8, u8, u8)> = HashMap::new();

    records.insert(String::from("google.com"), (142, 250, 67, 174));

    let (a, b, c, d) = records.get("google.com").unwrap();

    println!("The IP address of google.com is {}.{}.{}.{}", a, b, c, d);
}
