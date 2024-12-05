use super::{buffer::Buffer, ops_basic::BufferBasicOps};

pub trait BufferWithUIntOps: BufferBasicOps {
    fn read_as_u8(&mut self) -> Result<u8, &str>;
    fn write_u8(&mut self, byte: u8) -> Result<(), &str>;

    fn read_as_u16(&mut self) -> Result<u16, &str>;
    fn write_u16(&mut self, byte: u16) -> Result<(), &str>;

    fn read_as_u32(&mut self) -> Result<u32, &str>;
    fn write_u32(&mut self, byte: u32) -> Result<(), &str>;
}

impl<const MS: usize> BufferWithUIntOps for Buffer<MS> {
    fn read_as_u8(&mut self) -> Result<u8, &str> {
        if self.read_position >= 512 {
            return Err("Buffer end is reached (512 bytes). No more bytes can be read as u8.");
        }

        let byte = self.data[self.read_position as usize];
        self.read_position += 1;

        Ok(byte)
    }

    fn write_u8(&mut self, byte: u8) -> Result<(), &str> {
        self.write(byte)
    }

    fn read_as_u16(&mut self) -> Result<u16, &str> {
        if self.read_position + 2 >= 512 {
            return Err("Buffer end is reached (512 bytes). No more bytes can be read as u16.");
        }

        let byte1 = self.data[self.read_position as usize] as u16;
        let byte2 = self.data[(self.read_position + 1) as usize] as u16;
        self.read_position += 2;

        Ok((byte1 << 8) | byte2)
    }

    fn write_u16(&mut self, byte: u16) -> Result<(), &str> {
        self.write((byte >> 8) as u8)?;
        self.write((byte & 0xFF) as u8)?;

        Ok(())
    }

    fn read_as_u32(&mut self) -> Result<u32, &str> {
        if self.read_position + 4 >= 512 {
            return Err("Buffer end is reached (512 bytes). No more bytes can be read as u32.");
        }

        let byte1 = self.data[self.read_position as usize] as u32;
        let byte2 = self.data[(self.read_position + 1) as usize] as u32;
        let byte3 = self.data[(self.read_position + 2) as usize] as u32;
        let byte4 = self.data[(self.read_position + 3) as usize] as u32;
        self.read_position += 4;

        Ok((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4)
    }

    fn write_u32(&mut self, byte: u32) -> Result<(), &str> {
        self.write((byte >> 24) as u8)?;
        self.write((byte >> 16) as u8)?;
        self.write((byte >> 8) as u8)?;
        self.write((byte & 0xFF) as u8)
    }
}
