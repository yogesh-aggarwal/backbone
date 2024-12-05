pub struct PacketBuffer {
    pub data: [u8; 512],

    pub read_position: u16,
    pub write_position: u16,
}

impl PacketBuffer {
    pub fn new() -> PacketBuffer {
        PacketBuffer {
            data: [0; 512],
            read_position: 0,
            write_position: 0,
        }
    }

    pub fn get(&self) -> u8 {
        self.data[self.read_position as usize]
    }

    pub fn get_at(&self, position: u16) -> u8 {
        self.data[position as usize]
    }

    pub fn get_range(&mut self, start: u16, len: u16) -> Result<&[u8], &str> {
        if start + len >= 512 {
            return Err("End of buffer".into());
        }
        Ok(&self.data[(start as usize)..((start + len) as usize)])
    }

    pub fn step_read(&mut self, steps: u16) {
        self.read_position += steps;
    }

    pub fn step_write(&mut self, steps: u16) {
        self.write_position += steps;
    }

    pub fn seek_read(&mut self, position: u16) -> Result<(), &str> {
        /* Check for overflow */
        if position >= 512 {
            return Err(
                "Packet buffer end is reached (512 bytes). Cannot seek to the specified position.",
            );
        }

        self.read_position = position;

        Ok(())
    }

    pub fn seek_write(&mut self, position: u16) -> Result<(), &str> {
        /* Check for overflow */
        if position >= 512 {
            return Err(
                "Packet buffer end is reached (512 bytes). Cannot seek to the specified position.",
            );
        }

        self.write_position = position;

        Ok(())
    }

    pub fn read(&mut self) -> Result<u8, &str> {
        /* Check for overflow */
        if self.read_position >= 512 {
            return Err("Packet buffer end is reached (512 bytes). No more bytes can be read.");
        }

        let byte = self.data[self.read_position as usize];
        self.read_position += 1;

        Ok(byte)
    }

    pub fn read_as_u16(&mut self) -> Result<u16, &str> {
        /* Check for overflow */
        if self.read_position + 2 >= 512 {
            return Err(
                "Packet buffer end is reached (512 bytes). No more bytes can be read as u16.",
            );
        }

        let byte1 = self.data[(self.read_position + 0) as usize] as u16;
        let byte2 = self.data[(self.read_position + 1) as usize] as u16;
        self.read_position += 2;

        let result: u16 = (byte1 << 8) | (byte2 << 0);

        Ok(result)
    }

    pub fn read_as_u32(&mut self) -> Result<u32, &str> {
        /* Check for overflow */
        if self.read_position + 4 >= 512 {
            return Err(
                "Packet buffer end is reached (512 bytes). No more bytes can be read as u32.",
            );
        }

        let byte1 = self.data[(self.read_position + 0) as usize] as u32;
        let byte2 = self.data[(self.read_position + 1) as usize] as u32;
        let byte3 = self.data[(self.read_position + 2) as usize] as u32;
        let byte4 = self.data[(self.read_position + 3) as usize] as u32;
        self.read_position += 4;

        let result: u32 = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | (byte4 << 0);

        Ok(result)
    }

    /**
     * sample input: 3www6google3com0
     * sample output: www.google.com
     */
    pub fn read_qname(&mut self) -> Result<String, &str> {
        let mut qname = String::new();

        let mut jump_count = 0;
        let mut msb_based_jumped = false;

        let mut pos = self.read_position.clone();
        loop {
            if jump_count > 5 {
                return Err("Too many jumps while reading qname.");
            }

            let len = self.data[pos as usize];
            if len == 0 {
                break;
            }

            if (len & 0xC0) == 0xC0 {
                // When a jump is performed, we only modify the shared buffer
                // position once, and avoid making the change later on.
                if !msb_based_jumped {
                    if self.seek_read(pos + 2).is_err() {
                        return Err("Failed to seek read position after reading qname.");
                    }
                }

                let b2 = self.data[pos as usize + 1] as u16;
                let offset = (((len as u16) ^ 0xC0) << 8) | b2;
                pos = offset as u16;

                msb_based_jumped = true;
                jump_count += 1;

                continue;
            }

            /* Meaning that we have passed the initial jump */
            if pos != 0 {
                qname.insert_str(qname.len(), ".");
            }

            let start = pos + 1;
            let end = start + len as u16;
            let buffer = &self.data[start as usize..end as usize];
            qname.insert_str(qname.len(), &String::from_utf8_lossy(buffer));

            pos = end;
            jump_count += 1;
        }

        /* If we jumped means we read some data and hence the cursor needs to be reallocated */
        if jump_count > 0 {
            if self.seek_read(pos).is_err() {
                return Err("Failed to seek read position after reading qname.");
            }
        } else {
            /* We don't need to do anything as we only worked on a copy of our position :) */
        }

        Ok(qname)
    }

    pub fn write(&mut self, byte: u8) -> Result<(), &str> {
        /* Check for overflow */
        if self.write_position >= 512 {
            return Err("Packet buffer end is reached (512 bytes). No more bytes can be written.");
        }

        self.data[self.write_position as usize] = byte;
        self.write_position += 1;

        Ok(())
    }

    pub fn write_u16(&mut self, byte: u16) -> Result<(), &str> {
        /* We don't need to check for overflow as it's already done in the `write` function */
        if self.write((byte >> 8) as u8).is_err() {
            return Err("Failed to write the first byte of the u16.");
        }
        if self.write((byte >> 0) as u8).is_err() {
            return Err("Failed to write the second byte of the u16.");
        }

        Ok(())
    }

    pub fn write_u32(&mut self, byte: u32) -> Result<(), &str> {
        /* We don't need to check for overflow as it's already done in the `write` function */
        if self.write((byte >> 24) as u8).is_err() {
            return Err("Failed to write the first byte of the u32.");
        }
        if self.write((byte >> 16) as u8).is_err() {
            return Err("Failed to write the second byte of the u32.");
        }
        if self.write((byte >> 8) as u8).is_err() {
            return Err("Failed to write the third byte of the u32.");
        }
        if self.write((byte >> 0) as u8).is_err() {
            return Err("Failed to write the fourth byte of the u32.");
        }

        Ok(())
    }

    /**
     * sample input: www.google.com
     * sample output: 3www6google3com0
     */
    pub fn write_qname(&mut self, qname: &str) -> Result<(), &str> {
        let tokens = qname.split(".");
        for token in tokens {
            let len = token.len();

            /*
             * Check for exceeding lengths in which case it will invalid to
             * write & hence will raise error
             */
            if len > 63 {
                return Err("A label in the qname is too long.");
            }

            /* Write the length of the upcoming token first */
            if self.write(len as u8).is_err() {
                return Err("Failed to write the length of the label.");
            }

            /* Write the token itself */
            for char in token.as_bytes() {
                if self.write(*char).is_err() {
                    return Err("Failed to write the character of the label.");
                }
            }
        }

        Ok(())
    }
}
