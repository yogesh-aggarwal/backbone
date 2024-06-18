use std::{fs::File, io::Read};

use dns::{core::packet_buffer::PacketBuffer, dns_packet::DNSPacket};
use utility::result::Result;

mod dns {
    pub mod dns_header;
    pub mod dns_packet;
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

fn main() -> Result<()> {
    // clear the screen
    clearscreen::clear().expect("failed to clear screen");

    let mut f = File::open("response_packet.txt")?;

    let mut buffer = PacketBuffer::new();
    f.read(&mut buffer.data)?;

    println!("buffer: {:?}", buffer.read_position);

    let packet = DNSPacket::from_buffer(&mut buffer)?;
    // println!("{:#?}", packet.header);

    // for q in packet.questions {
    //     println!("{:#?}", q);
    // }
    // for rec in packet.answers {
    //     println!("{:#?}", rec);
    // }
    // for rec in packet.authorities {
    //     println!("{:#?}", rec);
    // }
    // for rec in packet.additionals {
    //     println!("{:#?}", rec);
    // }

    Ok(())
}
