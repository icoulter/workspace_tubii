#include "tubii_client.h"
#include "record_info.h"
#include "data.h"
#include "logging.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include "ae.h"
#include "server.h"

// tubii headers
#include "tubiiAddresses.h"
#include "tubiiClocks.h"
#include "tubiiELLIE.h"
#include "tubiiRegs.h"
#include "tubiiTriggers.h"
#include "tubiiUtil.h"


extern aeEventLoop *el;
int last_gtid=0;

// Initialisation functions
void initialise(client *c, int argc, sds *argv)
{
	// Calls auto_init which:
	//  -Maps all the memory
	//  -Sets registers
	auto_init();

	// Need to check for errors
	addReplyStatus(c, "+OK");
}

int InitMapping()
{
	// Ian: Do all the memory mappings on start up as it'll save time during each function call

	// Muxer & loadShift
	u32 RegsBaseAddress= SHIFTREGS_BASEADDR;
	u32 RegsHighAddress= SHIFTREGS_HIGHADDR;
	MappedRegsBaseAddress= MemoryMapping(RegsBaseAddress,RegsHighAddress);

	// Clocks
	u32 ClocksBaseAddress= CLOCKLOGIC_BASEADDR;
	u32 ClocksHighAddress= CLOCKLOGIC_HIGHADDR;
	MappedClocksBaseAddress= MemoryMapping(ClocksBaseAddress,ClocksHighAddress);

	// Counter Latch & Reset
	u32 CountBaseAddress= COUNTDISP_BASEADDR;
	u32 CountHighAddress= COUNTDISP_HIGHADDR;
	MappedCountBaseAddress= MemoryMapping(CountBaseAddress,CountHighAddress);

	// Trigger, Counter & Speaker Masks
	u32 TrigBaseAddress= TRIGGEROUT_BASEADDR;
	u32 TrigHighAddress= TRIGGEROUT_HIGHADDR;
	MappedTrigBaseAddress= MemoryMapping(TrigBaseAddress,TrigHighAddress);

	// Trig Fifo
	u32 FifoBaseAddress= FIFOREADOUT_BASEADDR;
	u32 FifoHighAddress= FIFOREADOUT_HIGHADDR;
	MappedFifoBaseAddress= MemoryMapping(FifoBaseAddress,FifoHighAddress);

	// Burst
	u32 BurstBaseAddress= BURSTTRIG_BASEADDR;
	u32 BurstHighAddress= BURSTTRIG_HIGHADDR;
	MappedBurstBaseAddress= MemoryMapping(BurstBaseAddress,BurstHighAddress);

	// Combo
	u32 ComboBaseAddress= COMBOTRIG_BASEADDR;
	u32 ComboHighAddress= COMBOTRIG_HIGHADDR;
	MappedComboBaseAddress= MemoryMapping(ComboBaseAddress,ComboHighAddress);

	// Prescale
	u32 PrescaleBaseAddress= PRESCALETRIG_BASEADDR;
	u32 PrescaleHighAddress= PRESCALETRIG_HIGHADDR;
	MappedPrescaleBaseAddress= MemoryMapping(PrescaleBaseAddress,PrescaleHighAddress);

	// Pulsers
	u32 PulserBaseAddress= GENERICPULSER_BASEADDR;
	u32 PulserHighAddress= GENERICPULSER_HIGHADDR;
	MappedPulserBaseAddress= MemoryMapping(PulserBaseAddress,PulserHighAddress);

	u32 SPulserBaseAddress= SMELLIEPULSER_BASEADDR;
	u32 SPulserHighAddress= SMELLIEPULSER_HIGHADDR;
	MappedSPulserBaseAddress= MemoryMapping(SPulserBaseAddress,SPulserHighAddress);

	u32 TPulserBaseAddress= TELLIEPULSER_BASEADDR;
	u32 TPulserHighAddress= TELLIEPULSER_HIGHADDR;
	MappedTPulserBaseAddress= MemoryMapping(TPulserBaseAddress,TPulserHighAddress);

	u32 HappyBaseAddress= MZHAPPY_BASEADDR;
	u32 HappyHighAddress= MZHAPPY_HIGHADDR;
	MappedHappyBaseAddress= MemoryMapping(HappyBaseAddress,HappyHighAddress);

	// Delays
	u32 DelayBaseAddress= GENERICDELAY_BASEADDR;
	u32 DelayHighAddress= GENERICDELAY_HIGHADDR;
	MappedDelayBaseAddress= MemoryMapping(DelayBaseAddress,DelayHighAddress);

	u32 SDelayBaseAddress= SMELLIEDELAY_BASEADDR;
	u32 SDelayHighAddress= SMELLIEDELAY_HIGHADDR;
	MappedSDelayBaseAddress= MemoryMapping(SDelayBaseAddress,SDelayHighAddress);

	u32 TDelayBaseAddress= TELLIEDELAY_BASEADDR;
	u32 TDelayHighAddress= TELLIEDELAY_HIGHADDR;
	MappedTDelayBaseAddress= MemoryMapping(TDelayBaseAddress,TDelayHighAddress);

	u32 GTDelayBaseAddress= GTDELAY_BASEADDR;
	u32 GTDelayHighAddress= GTDELAY_HIGHADDR;
	MappedGTDelayBaseAddress= MemoryMapping(GTDelayBaseAddress,GTDelayHighAddress);
}

int auto_init()
{
	// Final version should include things like safe trigger settings and MZHappy
	InitMapping();

	//Put caen in attenuating mode
	Muxer("1");
	MuxEnable("1");
	LoadShift(255);
	LoadShift(255);
	MuxEnable("0");
	DataReady("6");
	DataReady("4");
	//setup DGT and LO* delay lengths
	Muxer("3");
	MuxEnable("1");
	LoadShift(153);
	LoadShift(153);
	MuxEnable("0");
	//Set MTCA MIMIC DAC value
	Muxer("2");
	MuxEnable("1");
	MuxEnable("0");
	LoadShift(153);
	LoadShift(153);
	DataReady("0");
	DataReady("4");

	return 0;
}


// Clock commands
void clockreset(client *c, int argc, sds *argv)
{
	int ret= clockReset(1);
	usleep(1000);
	ret= clockReset(0);

	if(ret != 0){
	  addReplyError(c, tubii_err);
	  return;
	}

	addReplyStatus(c, "+OK");
}

void clockstatus(client *c, int argc, sds *argv)
{
	int status= clockStatus();

	// do something with ret which is the status of the backup clock
	// add to the datastream?

	addReply(c, ":%d", status);
}

void clockdebug(client *c, int argc, sds *argv)
{
	clockDebug();

	addReplyStatus(c, "+OK");
}

// Utility commands

void MZHappy(client *c, int argc, sds *argv)
{
	// Set for 1e9 pulses. Should renew this in the status readout.
	int ret= Pulser("1","0.5","1e9",MappedHappyBaseAddress);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void ping(client *c, int argc, sds *argv)
{
	addReplyStatus(c, "+PING");
}

void test(client *c, int argc, sds *argv)
{
	Testing(BURSTTRIG_BASEADDR,BURSTTRIG_HIGHADDR);
	Log(NOTICE, "TUBii: BurstTrig Memory Test ... OK");
	sleep(1);

	Testing(CLOCKLOGIC_BASEADDR,CLOCKLOGIC_HIGHADDR);
	Log(NOTICE, "TUBii: ClockLogic Memory Test ... OK");
	sleep(1);

	Testing(COMBOTRIG_BASEADDR,COMBOTRIG_HIGHADDR);
	Log(NOTICE, "TUBii: ComboTrig Memory Test ... OK");
	sleep(1);

	Testing(COUNTDISP_BASEADDR,COUNTDISP_HIGHADDR);
	Log(NOTICE, "TUBii: Display Memory Test ... OK");
	sleep(1);

	Testing(PRESCALETRIG_BASEADDR,PRESCALETRIG_HIGHADDR);
	Log(NOTICE, "TUBii: PrescaleTrig Memory Test ... OK");
	sleep(1);

	Testing(GENERICDELAY_BASEADDR,GENERICDELAY_HIGHADDR);
	Log(NOTICE, "TUBii: GenericDelay Memory Test ... OK");
	sleep(1);

	Testing(GTDELAY_BASEADDR,GTDELAY_HIGHADDR);
	Log(NOTICE, "TUBii: GTDelay Memory Test ... OK");
	sleep(1);

	Testing(SMELLIEDELAY_BASEADDR,SMELLIEDELAY_HIGHADDR);
	Log(NOTICE, "TUBii: SmellieDelay Memory Test ... OK");
	sleep(1);

	Testing(TELLIEDELAY_BASEADDR,TELLIEDELAY_HIGHADDR);
	Log(NOTICE, "TUBii: TellieDelay Memory Test ... OK");
	sleep(1);

	Testing(SHIFTREGS_BASEADDR,SHIFTREGS_HIGHADDR);
	Log(NOTICE, "TUBii: LoadShift Memory Test ... OK");
	sleep(1);

	Testing(MZHAPPY_BASEADDR,MZHAPPY_HIGHADDR);
	Log(NOTICE, "TUBii: MZHappy Memory Test ... OK");
	sleep(1);

	Testing(GENERICPULSER_BASEADDR,GENERICPULSER_HIGHADDR);
	Log(NOTICE, "TUBii: GenericPulser Memory Test ... OK");
	sleep(1);

	Testing(SMELLIEPULSER_BASEADDR,SMELLIEPULSER_HIGHADDR);
	Log(NOTICE, "TUBii: SmelliePulser Memory Test ... OK");
	sleep(1);

	Testing(TELLIEPULSER_BASEADDR,TELLIEPULSER_HIGHADDR);
	Log(NOTICE, "TUBii: TelliePulser Memory Test ... OK");
	sleep(1);

	Testing(TRIGGERSPLIT_BASEADDR,TRIGGERSPLIT_HIGHADDR);
	Log(NOTICE, "TUBii: TriggerSplit Memory Test ... OK");
	sleep(1);

	Testing(TRIGGEROUT_BASEADDR,TRIGGEROUT_HIGHADDR);
	Log(NOTICE, "TUBii: TriggerOut Memory Test ... OK");

	addReplyStatus(c, "+OK");
}

// ELLIE commands
void SetGenericpulser(client *c, int argc, sds *argv)
{
	// Need to sync. create pulse and delay it async.

	// 1. Create Pulse
	int ret1= Pulser(argv[1],argv[2],argv[3],MappedPulserBaseAddress);
	if(ret1!=0){
	  addReplyError(c, tubii_err);
	  return;
	}

	grate = atoi(argv[1]);
	gwidth = atoi(argv[2]);
	gnpulse = atoi(argv[3]);

	// 2. Delay Pulse
	/*int ret2= Muxer("4");
	int ret3= LoadShift(argv[1]);
    */
	addReplyStatus(c, "+OK");
}

void SetGenericdelay(client *c, int argc, sds *argv)
{
	// 1. Need to split argument into the sync part and async part
	// Something like multiples of 10 go to sync and ones go to async

	// 2. Sync part
	int ret1= Delay(argv[1],MappedDelayBaseAddress);
	if(ret1 != 0){
	  addReplyError(c, tubii_err);
	  return;
	}

	gdelay = atoi(argv[1]);

	// 3. Async part to shift reg:
	//int ret2= Muxer("5");
	//int ret3= LoadShift(argv[1]);

	addReplyStatus(c, "+OK");
}

void SetSmelliepulser(client *c, int argc, sds *argv)
{
	//int ret= Pulser(argv[1],argv[2],argv[3],MappedSPulserBaseAddress);
	int ret= Pulser(argv[1],argv[2],argv[3],MappedHappyBaseAddress);

	smrate = atoi(argv[1]);
	smwidth = atoi(argv[2]);
	smnpulse = atoi(argv[3]);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void SetSmelliedelay(client *c, int argc, sds *argv)
{
	int ret= Delay(argv[1],MappedSDelayBaseAddress);

	smdelay = atoi(argv[1]);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void SetTelliepulser(client *c, int argc, sds *argv)
{
	int ret= Pulser(argv[1],argv[2],argv[3],MappedTPulserBaseAddress);

	trate = atoi(argv[1]);
	twidth = atoi(argv[2]);
	tnpulse = atoi(argv[3]);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);;
}

void SetTelliedelay(client *c, int argc, sds *argv)
{
	int ret= Delay(argv[1],MappedTDelayBaseAddress);

	tdelay = atoi(argv[1]);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void GetSmellieRate(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", smrate);
}

void GetSmelliePulseWidth(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", smwidth);
}

void GetSmellieNPulses(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", smnpulse);
}

void GetSmellieDelay(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", smdelay);
}

void GetTellieRate(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", trate);
}

void GetTelliePulseWidth(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", twidth);
}

void GetTellieNPulses(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", tnpulse);
}

void GetTellieDelay(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", tdelay);
}

void GetPulserRate(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", grate);
}

void GetPulserWidth(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", gwidth);
}

void GetPulserNPulses(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", gnpulse);
}

void GetDelay(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", gdelay);
}

//// Shift Register commands
//   Low level stuff
void dataready(client *c, int argc, sds *argv)
{
	int ret= DataReady(argv[1]);

	if(ret==0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void loadShift(client *c, int argc, sds *argv)
{
	int ret= LoadShift(atoi(argv[1]));

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void muxenable(client *c, int argc, sds *argv)
{
	int ret= MuxEnable(argv[1]);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void muxer(client *c, int argc, sds *argv)
{
	int ret= Muxer(argv[1]);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

// Control register
void SetControlReg(client *c, int argc, sds *argv)
{
	Muxer("0");
	MuxEnable("1");
	LoadShift(atoi(argv[1]));
	MuxEnable("0");
	DataReady("5");
	DataReady("4");

	CntrlReg = atoi(argv[1]);

	addReplyStatus(c, "+OK");
}

void GetControlReg(client *c, int argc, sds *argv)
{
	int word= ReadShift();

	addReply(c, ":%d", word);
}

// CAEN Settings
void SetCaenWords(client *c, int argc, sds *argv)
{
	Muxer("1");
	MuxEnable("1");
	LoadShift(atoi(argv[1]));
	LoadShift(atoi(argv[2]));
	MuxEnable("0");
	DataReady("6");
	DataReady("4");

	GainPathWord = atoi(argv[1]);
	ChannelSelectWord = atoi(argv[2]);

	addReplyStatus(c, "+OK");
}

void GetCAENGainPathWord(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", GainPathWord);
}

void GetCAENChannelSelectWord(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", ChannelSelectWord);
}

// DAC Settings
void SetDACThreshold(client *c, int argc, sds *argv)
{
	DACThresh = atoi(argv[1]);

	int DACThresh_pt1 = DACThresh & 0xFF;
	int DACThresh_pt2 = DACThresh >> 8;

	Muxer("2");
	MuxEnable("1");
	MuxEnable("0");
	LoadShift(DACThresh_pt2);
	LoadShift(DACThresh_pt1);
	MuxEnable("0");
	DataReady("0");
	DataReady("4");

	addReplyStatus(c, "+OK");
}

void GetDACThreshold(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", DACThresh);
}

// DGT & LO
void SetGTDelays(client *c, int argc, sds *argv)
{
	Muxer("3");
	MuxEnable("1");
	LoadShift(atoi(argv[1]));
	LoadShift(atoi(argv[2]));
	MuxEnable("0");

	LODelay = atoi(argv[1]);
	DGTDelay = atoi(argv[2]);

	addReplyStatus(c, "+OK");
}

void GetLODelay(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", LODelay);
}

void GetDGTDelay(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", DGTDelay);
}

void SetAllowableClockMisses(client *c, int argc, sds *argv)
{
	// Do something and add get
}


// Trigger Commands
void SetCounterMask(client *c, int argc, sds *argv)
{
	int ret= counterMask(argv[1]);
	countMask = atoi(argv[1]);
	addReplyStatus(c, "+OK");
}

void GetCounterMask(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", countMask);
}

void countLatch(client *c, int argc, sds *argv)
{
	counterLatch(argv[1]);
	addReplyStatus(c, "+OK");
}

void countReset(client *c, int argc, sds *argv)
{
	counterReset(argv[1]);
	addReplyStatus(c, "+OK");
}

void gtdelay(client *c, int argc, sds *argv)
{
	int ret= Delay(argv[1],MappedGTDelayBaseAddress);

	if(ret == 0) addReplyStatus(c, "+OK");
	else addReplyError(c, tubii_err);
}

void SetSpeakerMask(client *c, int argc, sds *argv)
{
	int ret= speakerMask(argv[1]);
	speakMask = atoi(argv[1]);

	// Do something with ret
	addReplyStatus(c, "+OK");
}

void GetSpeakerMask(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", speakMask);
}






void SetTriggerMask(client *c, int argc, sds *argv)
{
	int ret= triggerMask(argv[1]);
	trigMask = atoi(argv[1]);

	addReplyStatus(c, "+OK");
}

void GetTriggerMask(client *c, int argc, sds *argv)
{
	addReply(c, ":%d", trigMask);
}

void trigBurst(client *c, int argc, sds *argv)
{
	// Does this work??
	burstTrig(argv[1]);
	addReplyStatus(c, "+OK");
}

void trigCombo(client *c, int argc, sds *argv)
{
	comboTrig(argv[1]);
	addReplyStatus(c, "+OK");
}

void trigPrescale(client *c, int argc, sds *argv)
{
	prescaleTrig(argv[1]);
	addReplyStatus(c, "+OK");
}

void GetCurrentTrigger(client *c, int argc, sds *argv)
{
    currentTrigger();
}

void GetFifoTrigger(client *c, int argc, sds *argv)
{
	int empty=0;
    struct MegaRecord mega;
	struct GenericRecordHeader header;

    mega.size=0;
    int loop=0;
	while(loop<1000){ //empty==0){
	//usleep(100);
    loop++;
	/* Send a TUBii_RECORD to the data stream server */
    struct TubiiRecord trec;
    fifoTrigger(&trec);

    if(last_gtid!=trec.GTID){
    if(last_gtid!=trec.GTID-1 && trec.GTID!=0) printf("Missed one! %i --> %i\n",last_gtid,trec.GTID);

    last_gtid=trec.GTID;
    printf("GTID %i Word %i\n",trec.GTID,trec.TrigWord);

    mega.array[mega.size]=trec;
    mega.size = mega.size+1;
    }
	}

	if(mega.size>0){
    printf("Bundle!\n");
    printf("%i events!\n",mega.size);

    header.RecordID = htonl(MEGA_RECORD);
    header.RecordLength = htonl(sizeof(mega));
    header.RecordVersion = htonl(RECORD_VERSION);

    write_to_data_stream(&header, &mega);
    }

    addReplyStatus(c, "+OK");
}

int tubii_status(aeEventLoop *el, long long id, void *data)
{
    /* Sends TUBii status record to the data stream */
    struct GenericRecordHeader header;
    struct TubiiStatus status;
    status.Clock = clockStatus();
    status.ControlReg = ReadShift();
    // Other stuff (FIFO status, reset MZHappy, counter rate)

    header.RecordID = htonl(TUBII_STATUS);
    header.RecordLength = htonl(sizeof(status));
    header.RecordVersion = htonl(RECORD_VERSION);

    /* convert to big endian */
    int i;
    for (i = 0; i < sizeof(status)/4; i++) {
        ((uint32_t *)&status)[i] = htonl(((uint32_t *)&status)[i]);
    }

    write_to_data_stream(&header, &status);

    return 1000; // run again in one second
    /* or, if you are done with this event */
    //return AE_NOMORE;
}


// Data readout
void start_data_readout(client *c, int argc, sds *argv)
{
	data_readout=1;
	addReplyStatus(c, "+OK");
}

void stop_data_readout(client *c, int argc, sds *argv)
{
	data_readout=0;
	addReplyStatus(c, "+OK");
}

int getDataReadout()
{
	return data_readout;
}

int start_tubii_readout(long long milliseconds)
{
    /*if (tubii_readout_id != AE_ERR) {
        sprintf(tubii_err, "TUBii: readout already running!");
        return -1;
    }*/
	printf("TRY TO START READOUT\n\n");
    //if(getDataReadout() == 0) return 0;

    // set up read out event
    if ((/*tubii_readout_id =*/ aeCreateTimeEvent(el, milliseconds, tubii_readout, NULL, NULL)) == AE_ERR) {
        sprintf(tubii_err, "failed to set up tubii readout");
        return -1;
    }

    return 0;
}

int tubii_readout(aeEventLoop *el, long long id, void *data)
{
	// Check if we want to read data
    if(getDataReadout() == 0) return 1000;

	struct MegaRecord mega;
	struct GenericRecordHeader header;

    mega.size=0;
    int loop=0;
    struct TubiiRecord trec;
	for(loop=0; loop<32000; loop++){
		/* Send a TUBii_RECORD to the data stream server */
		fifoTrigger(&trec);

		// Have we advanced?
		if(last_gtid!=trec.GTID){
			// Have we missed a tick
			if(last_gtid!=trec.GTID-1 && trec.GTID!=0) printf("Missed one! %i --> %i\n",last_gtid,trec.GTID);

			last_gtid=trec.GTID;
			//printf("Event %i -- %i\n",loop,trec.GTID);

			mega.array[mega.size]=trec;
			mega.size = mega.size+1;
		}
	}

	if(mega.size>0){
		//printf("Bundle! %i events!\n",mega.size);

		header.RecordID = htonl(MEGA_RECORD);
		header.RecordLength = htonl(sizeof(mega));
		header.RecordVersion = htonl(RECORD_VERSION);

		/* convert to big endian */
		/*int i;
    	for (i = 0; i < sizeof(trec)/4; i++) {
        ((uint32_t *)&trec)[i] = htonl(((uint32_t *)&trec)[i]);
    	}*/

		write_to_data_stream(&header, &mega);
    }

    return 1;
}



int safe_strtof(char *s, float *f)
{
    /* Convert string s -> float. Returns -1 on error. */
    char *end;

    errno = 0;
    *f = (float) strtod(s, &end);

    if (end == s) {
        return -1;
    } else if ('\0' != *end) {
        return -1;
    } else if (errno == ERANGE) {
        return -1;
    }

    return 0;
}

int safe_strtoul(char *s, uint32_t *si)
{
    /* Convert string s -> 32 bit unsigned integer. */
    char *end;
    
    errno = 0;
    *si = strtoul(s, &end, 0);

    if (end == s) {
        return -1;
    } else if ('\0' != *end) {
        return -1;
    } else if (errno == ERANGE) {
        return -1;
    }

    return 0;
}

int safe_strtoull(char *s, uint64_t *si)
{
    /* Convert string s -> 64 bit unsigned integer. */
    char *end;

    errno = 0;
    *si = strtoull(s, &end, 0);

    if (end == s) {
        return -1;
    } else if ('\0' != *end) {
        return -1;
    } else if (errno == ERANGE) {
        return -1;
    }

    return 0;
}