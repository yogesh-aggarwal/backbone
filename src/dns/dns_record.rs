pub struct DNSRecord {
    pub name: String,
    pub record_type: u16,
    pub class: u16,
    pub ttl: u16,
    pub data_length: u16,
}
