pub struct DNSQuestion {
    /**
     * Label sequence specifying the domain name to be resolved.
     */
    pub name: String,

    /**
     * 2-bytes
     *
     * The record type
     */
    pub question_type: u16,

    /**
     * 2-bytes
     *
     * The class, in practice always set to 1.
     */
    pub class: u16,
}
