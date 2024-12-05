use crate::{
    dns::{question::question::DNSQuestion, record::record::DNSRecord},
    utility::result::Result,
};

use super::{buffer::PacketBufferOps, header::PacketHeader};

#[derive(Clone, Debug)]
pub struct Packet {
    pub header: PacketHeader,
    pub questions: Vec<DNSQuestion>,
    pub answers: Vec<DNSRecord>,
    pub authorities: Vec<DNSRecord>,
    pub additionals: Vec<DNSRecord>,
}

impl Packet {
    pub fn new() -> Packet {
        Packet {
            header: PacketHeader::new(),
            questions: Vec::new(),
            answers: Vec::new(),
            authorities: Vec::new(),
            additionals: Vec::new(),
        }
    }

    pub fn from_buffer<T: PacketBufferOps>(buffer: &mut T) -> Result<Packet> {
        let mut result = Packet::new();

        /* Read header */
        result.header = PacketHeader::from_buffer(buffer)?;

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
