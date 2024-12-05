use crate::buffer::ops_basic::BufferBasicOps;
use dns::packet::{buffer::PacketBuffer, packet::Packet};
use std::{fs::File, io::Read};
use utility::result::Result;

mod buffer {
    pub mod buffer;
    pub mod ops_basic;
    pub mod ops_uint;
}

mod dns {
    pub mod packet {
        pub mod buffer;
        pub mod header;
        pub mod packet;
    }

    pub mod question {
        pub mod query_type;
        pub mod question;
    }

    mod record {
        pub mod record;
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

    let packet = Packet::from_buffer(&mut buffer)?;

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
