use super::buffer::Buffer;

pub trait BufferUIntOps {
    fn read_as_u8(&mut self) -> Result<u8, &str>;
    fn write_u8(&mut self, byte: u8) -> Result<(), &str>;

    fn read_as_u16(&mut self) -> Result<u16, &str>;
    fn write_u16(&mut self, byte: u16) -> Result<(), &str>;

    fn read_as_u32(&mut self) -> Result<u32, &str>;
    fn write_u32(&mut self, byte: u32) -> Result<(), &str>;
}

impl<const MS: usize> BufferUIntOps for Buffer<MS> {
    fn read_as_u8(&mut self) -> Result<u8, &str> {
        if self.read_position >= MS {
            return Err("Buffer end is reached. No more bytes can be read as u8.");
        }

        let byte = self.data[self.read_position];
        self.read_position += 1;

        Ok(byte)
    }

    fn write_u8(&mut self, byte: u8) -> Result<(), &str> {
        if self.read_position >= MS {
            return Err("Buffer end is reached. No more space to write u8.");
        }
        self.data[self.read_position] = byte;
        self.read_position += 1;
        Ok(())
    }

    fn read_as_u16(&mut self) -> Result<u16, &str> {
        if self.read_position + 2 > MS {
            return Err("Buffer end is reached. No more bytes can be read as u16.");
        }

        let byte1 = self.data[self.read_position] as u16;
        let byte2 = self.data[self.read_position + 1] as u16;
        self.read_position += 2;

        Ok((byte1 << 8) | byte2)
    }

    fn write_u16(&mut self, byte: u16) -> Result<(), &str> {
        if self.read_position + 2 > MS {
            return Err("Buffer end is reached. No more space to write u16.");
        }

        self.data[self.read_position] = (byte >> 8) as u8;
        self.data[self.read_position + 1] = (byte & 0xFF) as u8;
        self.read_position += 2;

        Ok(())
    }

    fn read_as_u32(&mut self) -> Result<u32, &str> {
        if self.read_position + 4 > MS {
            return Err("Buffer end is reached. No more bytes can be read as u32.");
        }

        let byte1 = self.data[self.read_position] as u32;
        let byte2 = self.data[self.read_position + 1] as u32;
        let byte3 = self.data[self.read_position + 2] as u32;
        let byte4 = self.data[self.read_position + 3] as u32;
        self.read_position += 4;

        Ok((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4)
    }

    fn write_u32(&mut self, byte: u32) -> Result<(), &str> {
        if self.read_position + 4 > MS {
            return Err("Buffer end is reached. No more space to write u32.");
        }

        self.data[self.read_position] = (byte >> 24) as u8;
        self.data[self.read_position + 1] = (byte >> 16) as u8;
        self.data[self.read_position + 2] = (byte >> 8) as u8;
        self.data[self.read_position + 3] = (byte & 0xFF) as u8;
        self.read_position += 4;

        Ok(())
    }
}
