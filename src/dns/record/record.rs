use crate::{
    dns::{packet::buffer::PacketBufferOps, question::query_type::DNSQuestionQueryType},
    utility::result::Result,
};
use std::net::Ipv4Addr;

#[derive(Debug, Clone, PartialEq, Eq, Hash, PartialOrd, Ord)]
#[allow(dead_code)]
pub enum DNSRecord {
    UNKNOWN {
        domain: String,
        qtype: u16,
        data_len: u16,
        ttl: u32,
    }, // 0
    A {
        domain: String,
        addr: Ipv4Addr,
        ttl: u32,
    }, // 1
}

impl DNSRecord {
    pub fn from_buffer<T: PacketBufferOps>(buffer: &mut T) -> Result<DNSRecord> {
        let mut domain = String::new();
        buffer
            .read_qname()
            .and_then(|qname| {
                domain = qname;
                Ok(())
            })
            .expect("Failed to read domain name from buffer.");

        let qtype_num = buffer.read_as_u16()?;
        let qtype = DNSQuestionQueryType::from_num(qtype_num);
        let _ = buffer.read_as_u16()?;
        let ttl = buffer.read_as_u32()?;
        let data_len = buffer.read_as_u16()?;

        match qtype {
            DNSQuestionQueryType::A => {
                let raw_addr = buffer.read_as_u32()?;
                let addr = Ipv4Addr::new(
                    ((raw_addr >> 24) & 0xFF) as u8,
                    ((raw_addr >> 16) & 0xFF) as u8,
                    ((raw_addr >> 8) & 0xFF) as u8,
                    ((raw_addr >> 0) & 0xFF) as u8,
                );

                Ok(DNSRecord::A {
                    domain: domain,
                    addr: addr,
                    ttl: ttl,
                })
            }
            DNSQuestionQueryType::UNKNOWN(_) => {
                buffer.step_read(data_len as usize);

                Ok(DNSRecord::UNKNOWN {
                    domain: domain,
                    qtype: qtype_num,
                    data_len: data_len,
                    ttl: ttl,
                })
            }
        }
    }
}
