struct send_Data
{
	unsigned char sequence_frame[1338];

	send_Data()
	{
		memset(sequence_frame, 0x00, sizeof(sequence_frame));
	}
};