use crate::buffer::{buffer::Buffer, ops_basic::BufferBasicOps, ops_uint::BufferUIntOps};

pub type PacketBuffer = Buffer<512>;

pub trait PacketBufferOps: BufferBasicOps + BufferUIntOps {
    fn read_qname(&mut self) -> Result<String, &str>;
    fn write_qname(&mut self, qname: &str) -> Result<(), &str>;
}

impl PacketBufferOps for PacketBuffer {
    fn read_qname(&mut self) -> Result<String, &str> {
        let mut qname = String::new();
        let mut jump_count = 0;
        let mut msb_based_jumped = false;
        let mut pos = self.read_position;

        loop {
            if jump_count > 5 {
                return Err("Too many jumps while reading qname.");
            }

            let len = self.data[pos];
            if len == 0 {
                break;
            }

            if (len & 0xC0) == 0xC0 {
                if !msb_based_jumped {
                    self.seek_read(pos + 2)?;
                }

                let b2 = self.data[(pos + 1) as usize];
                let offset = (((len) ^ 0xC0) << 8) | b2;
                pos = offset as usize;

                msb_based_jumped = true;
                jump_count += 1;
                continue;
            }

            if pos != 0 {
                qname.push('.');
            }

            let start = pos + 1;
            let end = start + len as usize;
            let buffer = &self.data[start as usize..end as usize];
            qname.push_str(&String::from_utf8_lossy(buffer));

            pos = end;
            jump_count += 1;
        }

        if jump_count > 0 {
            self.seek_read(pos)?;
        }

        Ok(qname)
    }

    fn write_qname(&mut self, qname: &str) -> Result<(), &str> {
        for token in qname.split('.') {
            let len = token.len();
            if len > 63 {
                return Err("A label in the qname is too long.");
            }

            self.write(len as u8)?;
            for &byte in token.as_bytes() {
                self.write(byte)?;
            }
        }

        self.write(0)
    }
}
