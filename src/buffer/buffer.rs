pub struct Buffer<const MAX_SIZE: usize> {
    pub data: [u8; MAX_SIZE],

    pub read_position: usize,
    pub write_position: usize,
}
