#[derive(PartialEq, Eq, Debug, Clone, Hash, Copy)]
pub enum QueryType {
    UNKNOWN(u16),
    A, // 1
       // AAAA,  // 28
       // NS,    // 2
       // CNAME, // 5
       // SOA,   // 6
       // PTR,   // 12
       // MX,    // 15
       // TXT,   // 16
       // SRV,   // 33
       // ANY,   // 255
}

impl QueryType {
    pub fn to_num(&self) -> u16 {
        match *self {
            QueryType::A => 1,
            // QueryType::AAAA => 28,
            // QueryType::NS => 2,
            // QueryType::CNAME => 5,
            // QueryType::SOA => 6,
            // QueryType::PTR => 12,
            // QueryType::MX => 15,
            // QueryType::TXT => 16,
            // QueryType::SRV => 33,
            // QueryType::ANY => 255,
            QueryType::UNKNOWN(x) => x,
        }
    }

    pub fn from_num(num: u16) -> QueryType {
        match num {
            1 => QueryType::A,
            // 28 => QueryType::AAAA,
            // 2 => QueryType::NS,
            // 5 => QueryType::CNAME,
            // 6 => QueryType::SOA,
            // 12 => QueryType::PTR,
            // 15 => QueryType::MX,
            // 16 => QueryType::TXT,
            // 33 => QueryType::SRV,
            // 255 => QueryType::ANY,
            _ => QueryType::UNKNOWN(num),
        }
    }
}
