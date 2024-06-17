use super::core::packet_buffer::PacketBuffer;
use crate::utility::result::Result;

pub struct DNSQuestion {
    /**
     * Label sequence specifying the domain name to be resolved.
     */
    pub name: String,

    /**
     * 2-bytes
     *
     * The record type
     */
    pub question_type: u16,

    /**
     * 2-bytes
     *
     * The class, in practice always set to 1.
     */
    pub class: u16,
}

impl DNSQuestion {
    pub fn new() -> DNSQuestion {
        DNSQuestion {
            name: String::new(),
            question_type: 0,
            class: 0,
        }
    }

    pub fn from_buffer(buffer: &mut PacketBuffer) -> Result<DNSQuestion> {
        let mut result = DNSQuestion::new();

        Ok(result)
    }
}
