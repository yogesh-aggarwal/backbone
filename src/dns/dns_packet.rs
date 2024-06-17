use crate::utility::result::Result;

use super::{
    core::packet_buffer::PacketBuffer, dns_header::DNSHeader, dns_question::DNSQuestion,
    dns_record::DNSRecord,
};

pub struct DNSPacket {
    pub header: DNSHeader,
    pub questions: Vec<DNSQuestion>,
    pub answers: Vec<DNSRecord>,
    pub authorities: Vec<DNSRecord>,
    pub additionals: Vec<DNSRecord>,
}

impl DNSPacket {
    pub fn new() -> DNSPacket {
        DNSPacket {
            header: DNSHeader::new(),
            questions: Vec::new(),
            answers: Vec::new(),
            authorities: Vec::new(),
            additionals: Vec::new(),
        }
    }

    pub fn from_buffer(buffer: &mut PacketBuffer) -> Result<DNSPacket> {
        let mut result = DNSPacket::new();

        /* Read header */
        result.header = DNSHeader::from_buffer(buffer)?;

        /* Read questions */
        for _ in 0..result.header.question_count {
            DNSQuestion::from_buffer(buffer)
                .and_then(|question| {
                    result.questions.push(question);
                    Ok(())
                })
                .expect("Failed to read question from buffer.");
        }

        /* Read answers */
        for _ in 0..result.header.answer_count {
            DNSRecord::from_buffer(buffer)
                .and_then(|record| {
                    result.answers.push(record);
                    Ok(())
                })
                .expect("Failed to read answer from buffer.");
        }

        /* Read authorities */
        for _ in 0..result.header.authority_count {
            DNSRecord::from_buffer(buffer)
                .and_then(|record| {
                    result.authorities.push(record);
                    Ok(())
                })
                .expect("Failed to read authority from buffer.");
        }

        /* Read additionals */
        for _ in 0..result.header.additional_count {
            DNSRecord::from_buffer(buffer)
                .and_then(|record| {
                    result.additionals.push(record);
                    Ok(())
                })
                .expect("Failed to read additional from buffer.");
        }

        Ok(result)
    }
}
