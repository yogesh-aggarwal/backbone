use super::buffer::Buffer;

/// A trait that defines basic operations for a buffer.
pub trait BufferBasicOps {
    /// Creates a new instance of the buffer.
    fn new() -> Self;

    /// Retrieves the current byte from the buffer.
    fn get(&self) -> u8;

    /// Retrieves the byte at the specified position in the buffer.
    ///
    /// ### Arguments
    ///
    /// * `position` - The position in the buffer from which to retrieve the byte.
    fn get_at(&self, position: usize) -> u8;

    /// Retrieves a range of bytes from the buffer.
    ///
    /// ### Arguments
    ///
    /// * `start` - The starting position of the range.
    /// * `len` - The length of the range.
    ///
    /// ### Returns
    ///
    /// A slice of bytes from the buffer, or an error message if the range is invalid.
    fn get_range(&self, start: usize, len: usize) -> Result<&[u8], &str>;

    /// Advances the read position by the specified number of steps.
    ///
    /// ### Arguments
    ///
    /// * `steps` - The number of steps to advance the read position.
    fn step_read(&mut self, steps: usize);

    /// Advances the write position by the specified number of steps.
    ///
    /// ### Arguments
    ///
    /// * `steps` - The number of steps to advance the write position.
    fn step_write(&mut self, steps: usize);

    /// Moves the read position to the specified position.
    ///
    /// ### Arguments
    ///
    /// * `position` - The position to move the read position to.
    ///
    /// ### Returns
    ///
    /// An empty result if successful, or an error message if the position is invalid.
    fn seek_read(&mut self, position: usize) -> Result<(), &str>;

    /// Moves the write position to the specified position.
    ///
    /// ### Arguments
    ///
    /// * `position` - The position to move the write position to.
    ///
    /// ### Returns
    ///
    /// An empty result if successful, or an error message if the position is invalid.
    fn seek_write(&mut self, position: usize) -> Result<(), &str>;

    /// Reads a byte from the current read position and advances the read position.
    ///
    /// ### Returns
    ///
    /// The byte read from the buffer, or an error message if the read fails.
    fn read(&mut self) -> Result<u8, &str>;

    /// Writes a byte to the current write position and advances the write position.
    ///
    /// ### Arguments
    ///
    /// * `byte` - The byte to write to the buffer.
    ///
    /// ### Returns
    ///
    /// An empty result if successful, or an error message if the write fails.
    fn write(&mut self, byte: u8) -> Result<(), &str>;
}

impl<const MS: usize> BufferBasicOps for Buffer<MS> {
    fn new() -> Self {
        Buffer {
            data: [u8::default(); MS],
            read_position: 0,
            write_position: 0,
        }
    }

    fn get(&self) -> u8 {
        self.data[self.read_position]
    }

    fn get_at(&self, position: usize) -> u8 {
        self.data[position]
    }

    fn get_range(&self, start: usize, len: usize) -> Result<&[u8], &str> {
        if start + len >= MS {
            return Err("End of buffer");
        }

        Ok(&self.data[(start)..(start + len)])
    }

    fn step_read(&mut self, steps: usize) {
        self.read_position.wrapping_add(steps.into());
    }

    fn step_write(&mut self, steps: usize) {
        self.write_position.wrapping_add(steps.into());
    }

    fn seek_read(&mut self, position: usize) -> Result<(), &str> {
        if position >= MS {
            return Err("Buffer end is reached. Cannot seek to the specified position.");
        }
        self.read_position = position.into();

        Ok(())
    }

    fn seek_write(&mut self, position: usize) -> Result<(), &str> {
        if position >= MS {
            return Err("Buffer end is reached. Cannot seek to the specified position.");
        }
        self.write_position = position.into();

        Ok(())
    }

    fn read(&mut self) -> Result<u8, &str> {
        if self.read_position >= MS {
            return Err("Buffer end is reached. No more bytes can be read.");
        }
        let byte = self.data[self.read_position];
        self.read_position += 1;

        Ok(byte)
    }

    fn write(&mut self, byte: u8) -> Result<(), &str> {
        if self.write_position >= MS {
            return Err("Buffer end is reached. No more bytes can be written.");
        }
        self.data[self.write_position] = byte;
        self.write_position += 1;

        Ok(())
    }
}
