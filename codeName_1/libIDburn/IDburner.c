#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
//#include <linux/genhd.h>
#include <android/log.h>
#include <mtd/mtd-abi.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <netinet/in.h>
#include <linux/if.h>
#include <linux/if_arp.h>
#include <sys/socket.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <android/log.h>

#include <stdio.h>
#include <string.h>

#include "cutils/properties.h"
#include "IDburner.h"
#include "i2c-dev.h"


//#include "efuse.h"
//#include "EDSV_Key.h"
//#include "blkinand.h"
#include "sdi2/sdi2_i2c.h"

#define MAC_SN_ATTAVH	"/sys/class/unifykeys/attach"	
#define MAC_SN_NAME		"/sys/class/unifykeys/name"
#define MAC_SN_WRITE	"/sys/class/unifykeys/write"
#define MAC_SN_READ		"/sys/class/unifykeys/read"

#define MAX_STR_LEN         4096

#define MODE_AUTO	0
#define MODE_QUICK	1
#define MODE_READ	2
#define MODE_FUNC	3

void OSThreadSleep(unsigned int uMilliSeconds)
{
	struct timespec delay;
	struct timespec rem;
	int rc;
	if (uMilliSeconds == 0) {
		return;
	}
	delay.tv_sec = (int) uMilliSeconds / 1000;
	delay.tv_nsec = 1000 * 1000 * (uMilliSeconds % 1000);
	for (;;) {
		rc = nanosleep(&delay, &rem);	/* [u]sleep can't be used because it uses SIGALRM */
		if (rc != 0) {
			if (errno == EINTR) {
				delay = rem;	/* sleep again */
				continue;
			}
			return;
		}
		break;					/* done */
	}
	return;
}

int I2cRead(unsigned long dwStartAddress, unsigned char * pucData, unsigned int  uDataLength , unsigned int  devAddr)
{
	SDI_INT32 ret = 0;
	SDI_Error_Code err = SDI_SUCCESS;
	I2COpenParam_S sI2Cparam = {0};
	SDI_HANDLE hI2C = SDI_NULL;
	SDI_UINT8 tmpAddr = 0;

	if (!pucData)
	{
		DError("pucData is NULL!");
		return ret;
	}

	tmpAddr = dwStartAddress;
	sI2Cparam.BlockIndex = I2C_BLOCK2;
	sI2Cparam.I2CSpeed      = I2C_SPEED_100K;
	sI2Cparam.TimeOut = 20;

	err = SDII2COpen(&sI2Cparam, &hI2C);
	if ((err != SDI_SUCCESS) || (hI2C == SDI_NULL))
	{
	        DError("%s_%d: SDII2COpen error, err:%d, hI2C:%d\n",__FUNCTION__,__LINE__,err,hI2C);
	        return ret;
	}
	else
	{
		DError("open SDII2COpen success!\n");
	}

	ret = SDII2CReadWithRegAddr(hI2C, devAddr, &tmpAddr, 1, pucData, uDataLength);
	if (ret != D_SUCCESS)
	{
		DError("read dm2016 dongle failed!\n");
	}
	else
	{
		DError("read dongle 2016 success!\n");
	}

	SDII2CClose(hI2C);

	return ret;
}

int I2cWrite(unsigned long dwStartAddress, const unsigned char * pucData, unsigned int  uDataLength, unsigned int  devAddr)
{
	SDI_INT32 i = 0;
	SDI_INT32 ret = 0;
	SDI_Error_Code err = SDI_SUCCESS;
	I2COpenParam_S sI2Cparam = {0};
	SDI_HANDLE hI2C = SDI_NULL;
	SDI_UINT8 tmpAddr = 0;

	if (!pucData)
	{
		DError("pucData is NULL!");
		return ret;
	}

	tmpAddr = dwStartAddress;
	sI2Cparam.BlockIndex = I2C_BLOCK2;
	sI2Cparam.I2CSpeed      = I2C_SPEED_100K;
	sI2Cparam.TimeOut = 20;

	err = SDII2COpen(&sI2Cparam, &hI2C);
	if ((err != SDI_SUCCESS) || (hI2C == SDI_NULL))
	{
	        DError("%s_%d: SDII2COpen error, err:%d, hI2C:%d\n",__FUNCTION__,__LINE__,err,hI2C);
	        return ret;
	}
	else
	{
		DError("open SDII2COpen success!\n");
	}

	while (i < uDataLength)
	{
		ret = SDII2CWriteWithRegAddr(hI2C, devAddr, &tmpAddr, 1, &pucData[i], 1);
		if (ret != D_SUCCESS)
		{
			DError("write dm2016 tmpAddr = %d failed!\n", tmpAddr);
			goto write_error;
		}
		else
		{
			DError("write dongle 2016 success!\n");
		}

		//write buff deley
		usleep(WRITE_DATA_DELAY);

		i++;
		tmpAddr++;
	}

write_error:
	SDII2CClose(hI2C);

	return ret;
}

int EPRRead(unsigned long dwStartAddress, unsigned char * pucData, unsigned int  uDataLength )
{
	SDI_INT32 ret = 0;
	SDI_Error_Code err = SDI_SUCCESS;
	I2COpenParam_S sI2Cparam = {0};
	SDI_HANDLE hI2C = SDI_NULL;
	SDI_UINT8 tmpAddr = 0;

	if (!pucData)
	{
		DError("pucData is NULL!");
		return ret;
	}
	
	tmpAddr = dwStartAddress;
	sI2Cparam.BlockIndex = I2C_BLOCK2;
	sI2Cparam.I2CSpeed      = I2C_SPEED_100K;
	sI2Cparam.TimeOut = 20;
	
	err = SDII2COpen(&sI2Cparam, &hI2C);
	if ((err != SDI_SUCCESS) || (hI2C == SDI_NULL))
	{
	        DError("%s_%d: SDII2COpen error, err:%d, hI2C:%d\n",__FUNCTION__,__LINE__,err,hI2C);
	        return ret;
	}
	else
	{
		DError("open SDII2COpen success!\n");
	}  
	
	ret = SDII2CReadWithRegAddr(hI2C, DM2016_DEV_ADDR, &tmpAddr, 1, pucData, uDataLength);
	if (ret != D_SUCCESS)
	{
		DError("read dm2016 dongle failed!\n");
	}
	else
	{
		DError("read dongle 2016 success!\n");
	}

	SDII2CClose(hI2C);
	
	return ret;
}

int EPRWrite(unsigned long dwStartAddress, const unsigned char * pucData, unsigned int  uDataLength)
{
	SDI_INT32 i = 0;
	SDI_INT32 ret = 0;
	SDI_Error_Code err = SDI_SUCCESS;
	I2COpenParam_S sI2Cparam = {0};
	SDI_HANDLE hI2C = SDI_NULL;
	SDI_UINT8 tmpAddr = 0;

	if (!pucData)
	{
		DError("pucData is NULL!");
		return ret;
	}
	
	tmpAddr = dwStartAddress;
	sI2Cparam.BlockIndex = I2C_BLOCK2;
	sI2Cparam.I2CSpeed      = I2C_SPEED_100K;
	sI2Cparam.TimeOut = 20;
	
	err = SDII2COpen(&sI2Cparam, &hI2C);
	if ((err != SDI_SUCCESS) || (hI2C == SDI_NULL))
	{
	        DError("%s_%d: SDII2COpen error, err:%d, hI2C:%d\n",__FUNCTION__,__LINE__,err,hI2C);
	        return ret;
	}
	else
	{
		DError("open SDII2COpen success!\n");
	}  
	
	while (i < uDataLength)	
	{
		ret = SDII2CWriteWithRegAddr(hI2C, DM2016_DEV_ADDR, &tmpAddr, 1, &pucData[i], 1);
		if (ret != D_SUCCESS)
		{
			DError("write dm2016 tmpAddr = %d failed!\n", tmpAddr);
			goto write_error;
		}
		else
		{
			DError("write dongle 2016 success!\n");
		}

		//write buff deley
		usleep(WRITE_DATA_DELAY);
		
		i++;
		tmpAddr++;
	}	

write_error:	
	SDII2CClose(hI2C);
	
	return ret;
}
#if 0
int EPRRead(unsigned long dwStartAddress, unsigned char * pucData, unsigned int  uDataLength )
{
	int nRet = -1;
	signed long		nI2C_Handle = -1;
	signed long		i;
	unsigned char	ucRegAddr=0;
		
	struct i2c_rdwr_ioctl_data work_queue;
	if(dwStartAddress > EEPROM_MAX_SIZE)
	{
		DError("EPRRead: dwStartAddress invalid\n");	
		return -1;
	}
	if(!pucData || (dwStartAddress+uDataLength) > EEPROM_MAX_SIZE)
	{
		DError("EPRRead: invalid params\n");	
		return -2;		
	}

		
	
	nI2C_Handle=open(I2C_EEP_FILE, O_RDWR);
	if(nI2C_Handle < 0)
	{
	  	DError("open %s fail, %d\n" , I2C_EEP_FILE , nI2C_Handle);
	  	return -1;
	}
	else
	{
	  	//DError("open %s, %d\n" , I2C_EEP_FILE , nI2C_Handle);
	}
	nRet = ioctl(nI2C_Handle, I2C_TIMEOUT, 20/ 10);
        if(nRet != 0)
        {
            DError("set timeout error, %ld\n", nRet);
        }
	
	memset(&work_queue, 0, sizeof(struct i2c_rdwr_ioctl_data));
	work_queue.nmsgs = 2; /* 消息数量 */
	work_queue.msgs = (struct i2c_msg*)malloc(work_queue.nmsgs *sizeof(struct i2c_msg));
	if (!work_queue.msgs)
	{
		DError("Memory alloc error\n");
		if(close(nI2C_Handle)<0)
		{
			DError("close %s fail\n" , I2C_EEP_FILE);	
		}
		return -1;
	}	
	memset(work_queue.msgs, 0, work_queue.nmsgs *sizeof(struct i2c_msg));

	
	ucRegAddr = dwStartAddress&0xff;
	work_queue.nmsgs = MAX_I2C_MSG;
	memset(work_queue.msgs, 0, work_queue.nmsgs *sizeof(struct i2c_msg));
	work_queue.msgs[0].flags = I2C_M_TEN;
  	work_queue.msgs[0].addr = (EEPROM_DEVICE_ADDR >> 1);
  	work_queue.msgs[0].buf = &ucRegAddr;
  	work_queue.msgs[0].len = 1;
  	work_queue.msgs[1].flags = I2C_M_RD;
  	work_queue.msgs[1].addr = (EEPROM_DEVICE_ADDR >> 1);
  	work_queue.msgs[1].buf = pucData;
  	work_queue.msgs[1].len = uDataLength;		
	nRet = ioctl(nI2C_Handle, I2C_RDWR, (unsigned long) &work_queue);	
	if(nRet < 0)
	{	
		if(close(nI2C_Handle)<0)
		{
			DError("close %s fail\n" , I2C_EEP_FILE);	
		}
		DError("EPRRead: ioctl  failed\n");	
		nRet = -3;
	}

	if(close(nI2C_Handle)<0)
	{
		DError("close %s fail\n" , I2C_EEP_FILE);	
	}

	free(work_queue.msgs);
	#if 0
	for(i=0;i<uDataLength;i++){
		DError("EPRRead success: 0x%x \n",pucData[i]);
	}
	#endif
	return 0;
}


int EPRWrite(unsigned long dwStartAddress, const unsigned char * pucData, unsigned int  uDataLength)
{

	int nRet = -1;
	signed long		nI2C_Handle = -1;
	unsigned char		pWriteBuf[16]={0};
	unsigned int		i = 0;
	struct i2c_rdwr_ioctl_data work_queue;	
			
	if(dwStartAddress > EEPROM_MAX_SIZE)
	{
		DError("EPRWrite: dwStartAddress invalid\n");	
		return -2;
	}
	
	if(!pucData || (dwStartAddress+uDataLength) > EEPROM_MAX_SIZE)
	{
		DError("EPRWrite: invalid params\n");	
		return -1;		
	}
	
	#if 0
	for(i=0;i<uDataLength;i++){
		DInfo("EPRWrite success: 0x%x \n",pucData[i]);
	}
	#endif
	
	nI2C_Handle=open(I2C_EEP_FILE, O_RDWR);
	if(nI2C_Handle < 0)
	{
	  	DError("open %s fail, %d\n" , I2C_EEP_FILE , nI2C_Handle);
	  	return -3;
	}
	else
	{
	  	//DError("open %s, %d\n" , I2C_EEP_FILE , nI2C_Handle);
	}
	nRet = ioctl(nI2C_Handle, I2C_TIMEOUT, 20/ 10);
        if(nRet != 0)
        {
        	DError("set timeout error, %ld\n", nRet);
        }
	memset(&work_queue, 0, sizeof(struct i2c_rdwr_ioctl_data));
	work_queue.nmsgs = 2; /* 消息数量 */
	work_queue.msgs = (struct i2c_msg*)malloc(work_queue.nmsgs *sizeof(struct i2c_msg));
	if (!work_queue.msgs)
	{
		 DError("Memory alloc error\n");
		 if(close(nI2C_Handle)<0)
		 {
			DError("close %s fail\n" , I2C_EEP_FILE);	
		 }
		 return -1;
	}	
	memset(work_queue.msgs, 0, work_queue.nmsgs *sizeof(struct i2c_msg));

	for(i=0;i<uDataLength;i++)
	{
		//DError("uDataLength = %d\n",uDataLength);
		pWriteBuf[0] = (dwStartAddress+i)&0xff;
		pWriteBuf[1] = pucData[i];
		work_queue.nmsgs = MAX_I2C_MSG;
		memset(work_queue.msgs, 0, work_queue.nmsgs *sizeof(struct i2c_msg));
		work_queue.msgs[0].flags=I2C_M_TEN;
		work_queue.msgs[0].buf=pWriteBuf;
		work_queue.msgs[0].len=2;
		work_queue.msgs[0].addr = (EEPROM_DEVICE_ADDR >> 1);

		nRet = ioctl(nI2C_Handle , I2C_RDWR, (unsigned long) &work_queue);	
		if(nRet < 0)
		{
			if(close(nI2C_Handle)<0)
			{
				DError("Error: close %s fail\n" , I2C_EEP_FILE);	
			}
			DError("Error: ioctl I2C_RDWR failed, i = %d,%d(%s)\n" , i,errno,strerror(errno));
			//add by Ronny
			free(work_queue.msgs); 
			close(nI2C_Handle);
			return -3;
		}	
		
		OSThreadSleep(EEPROM_WRITE_DELAY_MS);
	}
	

	if(close(nI2C_Handle)<0)
	{
		DError("close  %s fail\n" , I2C_EEP_FILE);	
	}

	free(work_queue.msgs); //add by Ronny
	return 0;
}
#endif

int open_i2c_dev(int i2cbus, char *filename, size_t size, int quiet)
{
	int file;

	snprintf(filename, size, "/dev/i2c/%d", i2cbus);
	filename[size - 1] = '\0';
	file = open(filename, O_RDWR);

	if (file < 0 && (errno == ENOENT || errno == ENOTDIR)) {
		sprintf(filename, "/dev/i2c-%d", i2cbus);
		file = open(filename, O_RDWR);
	}

	if (file < 0 && !quiet) {
		if (errno == ENOENT) {
			fprintf(stderr, "Error: Could not open file "
				"`/dev/i2c-%d' or `/dev/i2c/%d': %s\n",
				i2cbus, i2cbus, strerror(ENOENT));
		} else {
			fprintf(stderr, "Error: Could not open file "
				"`%s': %s\n", filename, strerror(errno));
			if (errno == EACCES)
				fprintf(stderr, "Run as root?\n");
		}
	}

	return file;
}

static int scan_i2c_bus(int file, int mode, int first, int last)
{
	int i, j;
	int res;
	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");

	for (i = 0; i < 128; i += 16) {
		printf("%02x: ", i);
		for(j = 0; j < 16; j++) {
			fflush(stdout);

			/* Skip unwanted addresses */
			if (i+j < first || i+j > last) {
				printf("   ");
				continue;
			}

			/* Set slave address */
			if (ioctl(file, I2C_SLAVE, i+j) < 0) {
				if (errno == EBUSY) {
					printf("UU ");
					continue;
				} else {
					fprintf(stderr, "Error: Could not set "
						"address to 0x%02x: %s\n", i+j,
						strerror(errno));
					return -1;
				}
			}

			/* Probe this address */
			switch (mode) {
			case MODE_QUICK:
				/* This is known to corrupt the Atmel AT24RF08
				   EEPROM */
				res = i2c_smbus_write_quick(file,
				      I2C_SMBUS_WRITE);
				break;
			case MODE_READ:
				/* This is known to lock SMBus on various
				   write-only chips (mainly clock chips) */
				res = i2c_smbus_read_byte(file);
				break;
			default:
				if ((i+j >= 0x30 && i+j <= 0x37)
				 || (i+j >= 0x50 && i+j <= 0x5F))
					res = i2c_smbus_read_byte(file);
				else
					res = i2c_smbus_write_quick(file,
					      I2C_SMBUS_WRITE);
			}

			if (res < 0)
				printf("-- ");
			else
				printf("%02x ", i+j);
		}
		printf("\n");
	}

	return 0;
}

static int isZeroEtherAddr(const char *addr)
{
	return !(addr[0] | addr[1] | addr[2] | addr[3] | addr[4] | addr[5]);
}

static int isMulticastEtherAddr(const char *addr)
{
        return ((addr[0] != 0xff) && (0x01 & addr[0]));
}

static int isMacValid(const char *pcMac)
{
	return !isZeroEtherAddr(pcMac) && !isMulticastEtherAddr(pcMac);
}

static int sdmc_get_sysfs_str(const char *path, char *value)
{
    int fd;
    int val = 0;
    char  bcmd[MAX_STR_LEN + 1] = { 0 };
	int len = 0;

    fd = open(path, O_RDONLY);
    if (fd >= 0) {
        len = read(fd, bcmd, sizeof(bcmd));
		DError("sdmc_get_sysfs_str:%d", len);
        close(fd);
    } else {
        DError("unable to open file %s,err: %s", path, strerror(errno));
    }

//	strcpy(value, bcmd);
	memcpy(value,bcmd,len);

    return val;
}

static int sdmc_fileecho(const char *name, const char *cmd, unsigned int  uDataLength)
{
	int fd, len, ret;
	
	if(NULL == name || NULL == cmd)
	{
		return -1;
	}
	
	fd = open(name, O_WRONLY);
	if(fd==-1)
	{
		printf("cannot open file \"%s\"\n", name);
		return -1;
	}
	//printf("open file \"%s\" ok\n", name);
	//len = strlen(cmd);
	len = uDataLength;
	
	ret = write(fd, cmd, len);
	if(ret!=len)
	{
		printf("write failed file:\"%s\" cmd:\"%s\" error:\"%s\"\n", name, cmd, strerror(errno));
		close(fd);
		return -1;
	}
	//printf("write file \"%s\" ok\n", name);
	close(fd);
	
	return 0;
}

int writeMacAddrToFlash(char *data, unsigned int  uDataLength)
{
	int nRet = -1;
	DError("==========writeMacAddrToFlash==========len:%d=uDataLength:%d=",strlen(data), uDataLength);
	nRet = sdmc_fileecho(MAC_SN_ATTAVH, "1", 1);
	nRet |= sdmc_fileecho(MAC_SN_NAME, "mac", 3);
	nRet |= sdmc_fileecho(MAC_SN_WRITE, data, uDataLength);
	nRet |= sdmc_fileecho(MAC_SN_ATTAVH, "0", 1);
	return nRet;
}

int readMacAddrFromFlash(const char *data)
{
	int nRet = -1;
	DError("==========readMacAddrFromFlash==========len:%d==",strlen(data));
	nRet = sdmc_fileecho(MAC_SN_ATTAVH, "1", 1);
	nRet |= sdmc_fileecho(MAC_SN_NAME, "mac", 3);
	nRet |= sdmc_get_sysfs_str(MAC_SN_READ, data);
	nRet |= sdmc_fileecho(MAC_SN_ATTAVH, "0", 1);
	return nRet;
}


int writeMacAddr(const char *data)
{
	char value[PROPERTY_VALUE_MAX] = {0};

	if(!data)
	{
		return -1;
	}

	if(isMacValid(data))
	{
		int i = 0;
		for(i=0;i<6;i++)
		{
			DError("0x%x ",data[i]);
		}
		DError("\n");
		property_get("ro.sdmc.thirdpart", value, "0");
		if (!strncmp(value, "true", 4)) {
			return writeMacAddrToFlash(data, MAC_ADDR_LENGTH);
		}
		DError("==========writeMacAddrTodm2016============");
		return EPRWrite(MAC_ADDR_START , data, MAC_ADDR_LENGTH);
	}
	else
		return -1;
}

int readMacAddr(char *data)
{
	char value[PROPERTY_VALUE_MAX] = {0};
	int nRet = -1;

	if(!data)
	{
		return -1;
	}

	property_get("ro.sdmc.thirdpart", value, "0");
	if (!strncmp(value, "true", 4)) {
		nRet = readMacAddrFromFlash(data);
	}
	else{	
		DError("==========readMacAddrFromdm2016============");
		nRet = EPRRead(MAC_ADDR_START , data, MAC_ADDR_LENGTH);
	}
	if(isMacValid(data))
	{
		int i = 0;
		for(i=0;i<6;i++)
		{
			DError("0x%x ",data[i]);
		}
		DError("\n");	

		return 0;
	}
	else
	{
		int i = 0;
		for(i=0;i<6;i++)
		{
			DError("0x%x ",data[i]);
		}
		DError("\n");
		return -1;
	}
		
}

int readUserDeviceIDFromFlash(char *data)
{
	int nRet = -1;

	DError("==========readUserDeviceIDFromFlash============");
	nRet = sdmc_fileecho(MAC_SN_ATTAVH, "1", 1);
	nRet |= sdmc_fileecho(MAC_SN_NAME, "usid", 4);
	nRet |= sdmc_get_sysfs_str(MAC_SN_READ, data);
	nRet |= sdmc_fileecho(MAC_SN_ATTAVH, "0", 1);
	return nRet;
}

int writeUserDeviceIDToFlash(const char *data, unsigned int  uDataLength)
{
	int nRet = -1;
	DError("==========writeUserDeviceIDToFlash============");
	nRet = sdmc_fileecho(MAC_SN_ATTAVH, "1", 1);
	nRet |= sdmc_fileecho(MAC_SN_NAME, "usid", 4);
	nRet |= sdmc_fileecho(MAC_SN_WRITE, data, USER_DEVICE_ID_ADDR_LENGTH);
	nRet |= sdmc_fileecho(MAC_SN_ATTAVH, "0", 1);
	return nRet;
}

int readUserDeviceID(char *data)
{
	char value[PROPERTY_VALUE_MAX] = {0};

	if(!data)
	{
		return -1;
	}
	
	property_get("ro.sdmc.thirdpart", value, "0");
	if (!strncmp(value, "true", 4)) {
		return readUserDeviceIDFromFlash(data);
	}
	DError("==========readUserDeviceIDFromDM2016============");
	return EPRRead(USER_DEVICE_ID_ADDR_START , data, USER_DEVICE_ID_ADDR_LENGTH);
}

int writeUserDeviceID(const char *data)
{
	char value[PROPERTY_VALUE_MAX] = {0};

	if(!data)
	{
		return -1;
	}
	
	property_get("ro.sdmc.thirdpart", value, "0");
	if (!strncmp(value, "true", 4)) {
		return writeUserDeviceIDToFlash(data, USER_DEVICE_ID_ADDR_LENGTH);
	}
	DError("==========writeUserDeviceIDDM2016============");
	return EPRWrite(USER_DEVICE_ID_ADDR_START , data, USER_DEVICE_ID_ADDR_LENGTH);
}

int readUserPrivateID(char *data)
{
	if(!data)
	{
		return -1;
	}

	return EPRRead(USER_PRIVATE_ID_ADDR_START , data, USER_PRIVATE_ID_ADDR_LENGTH);
	
}

int writeUserPrivateID(const char *data)
{
	if(!data)
	{
		return -1;
	}
	
	return EPRWrite(USER_PRIVATE_ID_ADDR_START , data, USER_PRIVATE_ID_ADDR_LENGTH);
	
}

int readUserHardwareVersionID(char *data)
{
	if(!data)
	{
		return -1;
	}

	return EPRRead(USER_HARDWARE_VERSION_ID_START , data, USER_HARDWARE_VERSION_ID_LENGTH);
	
}

int writeUserHardwareVersionID(const char *data)
{
	if(!data)
	{
		return -1;
	}
	
	return EPRWrite(USER_HARDWARE_VERSION_ID_START , data, USER_HARDWARE_VERSION_ID_LENGTH);
	
}

int edsv_keyBurn(const char *keyPath, const char *macAddr)
{
	return 0;
}

int edsv_keyCheck(const char *keyPath, const char *macAddr)
{
	return 0;
}

int hdcp_is_written(int *is_written)
{
	return 0;
}

int hdcp_write_key(const char *path)
{
	return 0;
}

int hdcp_get_used_keynum(const char *path, int *used_num)
{
	return 0;
}

int hdcp_get_unused_keynum(const char *path, int *unused_num)
{
	return 0;
}

int hdcp_file_is_valid(const char *path, int *is_valid)
{
	return 0;
}

int writeMac2Addr(const char *data)
{
	if(!data)
	{
		return -1;
	}
	if(isMacValid(data))
	{
		return EPRWrite(MAC2_ADDR_START , data, MAC_ADDR_LENGTH);
	}
	else
		return -1;
}

int readMac2Addr(char *data)
{
	if(!data)
	{
		return -1;
	}

	int nRet = EPRRead(MAC2_ADDR_START , data, MAC_ADDR_LENGTH);
	
	if(isMacValid(data))
	{
		return 0;
	}
	else
	{
		int i = 0;
		for(i=0;i<6;i++)
		{
			DError("0x%x ",data[i]);
		}
		DError("\n");
		return -1;
	}
		
}


#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include <fcntl.h>
#include <time.h>

#define TDATA32F 0xffffffff
#define TDATA32A 0xaaaaaaaa
#define TDATA325 0x55555555

#define DEFAULT_SIZE 0x2000000
#define BUFFER_LENGTH 32*1024*1024

static void ddr_write(void *buff, unsigned m_length)
{
    unsigned *p;
    unsigned i, j, n;
    unsigned m_len = m_length;
    
    p = (unsigned *)buff;
    
    while(m_len)
    {
        for(j=0;j<32;j++)
        {
            if(m_len >= 128)
                n = 32;
            else
                n = m_len>>2;
            
            for(i = 0; i < n; i++)
            {
                switch(i)
                {
                    case 0:
                    case 9:
                    case 14:
                    case 25:
                    case 30:
                        *(p+i) = TDATA32F;
                        break;
                    case 1:
                    case 6:
                    case 8:
                    case 17:
                    case 22:
                        *(p+i) = 0;
                        break;
                    case 16:
                    case 23:
                    case 31:                    
                        *(p+i) = TDATA32A;
                        break;
                    case 7:
                    case 15:
                    case 24:
                        *(p+i) = TDATA325;
                        break;
                    case 2:
                    case 4:
                    case 10:
                    case 12:
                    case 19:
                    case 21:
                    case 27:
                    case 29:
                        *(p+i) = 1<<j;
                        break;
                    case 3:
                    case 5:
                    case 11:
                    case 13:
                    case 18:
                    case 20:
                    case 26:
                    case 28:
                        *(p+i) = ~(1<<j);
                        break;
                }
            }
            
            if(m_len > 128)
            {
                m_len -= 128;
                p += 32;
            }
            else
            {
                p += (m_len>>2);
                m_len = 0;                
                break;
            }
        }
    }
}


static int ddr_read(void *buff, unsigned m_length)
{
    unsigned *p;
    unsigned i, j, n;
    unsigned m_len = m_length;
    int err_flag = 0;
    
    p = (unsigned *)buff;
    
    while(m_len)
    {
        for(j=0;j<32;j++)
        {
            if(m_len >= 128)
                n = 32;
            else
                n = m_len>>2;
            
            for(i = 0; i < n; i++)
            {
                switch(i)
                {
                    case 0:
                    case 9:
                    case 14:
                    case 25:
                    case 30:
                        if(*(p+i) != TDATA32F){
                            err_flag = 1;
                        }
                        break;
                    case 1:
                    case 6:
                    case 8:
                    case 17:
                    case 22:
                        if(*(p+i) != 0){
                            err_flag = 1;
                        }
                        break;
                    case 16:
                    case 23:
                    case 31:                    
                        if(*(p+i) != TDATA32A){
                            err_flag = 1;
                        }
                        break;
                    case 7:
                    case 15:
                    case 24:
                        if(*(p+i) != TDATA325){
                            err_flag = 1;
                        }
                        break;
                    case 2:
                    case 4:
                    case 10:
                    case 12:
                    case 19:
                    case 21:
                    case 27:
                    case 29:
                        if(*(p+i) != 1<<j){
                            err_flag = 1;
                        }
                        break;
                    case 3:
                    case 5:
                    case 11:
                    case 13:
                    case 18:
                    case 20:
                    case 26:
                    case 28:
                        if(*(p+i) != ~(1<<j)){
                            err_flag = 1;
                        }
                        break;
                } 
                err_flag = 0;

            }
            
            if(m_len > 128)
            {
                m_len -= 128;
                p += 32;
            }
            else
            {
                p += (m_len>>2);
                m_len = 0;
                break;
            }
        }
    }
    return err_flag;
}



int ddrTest(int nCount)
{
	int nRet = 0;
	char *pBuff = NULL;
	while(nCount)
	{
		char *pBuff = (char *)malloc(BUFFER_LENGTH);
		if(pBuff)
		{
			ddr_write(pBuff, BUFFER_LENGTH);
			nRet = ddr_read(pBuff, BUFFER_LENGTH);
			nRet = ddr_read(pBuff, BUFFER_LENGTH);
			nRet = ddr_read(pBuff, BUFFER_LENGTH);
			if(nRet != 0)
			{
				free(pBuff);
				return -1;
			}	
			free(pBuff);
		}else{
			return -2;
		}
		nCount--;
	}
	
	return 0;
}


int readActivecode(char* activeCode)
{
	return EPRRead(ACTIVE_CODE_ADDR_START , activeCode, ACTIVE_CODE_ADDR_LENGTH);
}

int writeActivecode(char* activeCode)
{
	return EPRWrite(ACTIVE_CODE_ADDR_START , activeCode, ACTIVE_CODE_ADDR_LENGTH);
}

int getTunerType(char* tunerType)
{
	return EPRRead(USER_TUNER_TYPE_ADDR_TYPE , tunerType, USER_TUNER_TYPE_ADDR_LENGTH);
}

int setTunerType(char* tunerType)
{
	return EPRWrite(USER_TUNER_TYPE_ADDR_TYPE , tunerType, USER_TUNER_TYPE_ADDR_LENGTH);
}

int readSN(char* sn)
{
	char tmp[USER_DEVICE_ID_ADDR_LENGTH]={0};
	if(readUserDeviceID(tmp)<0)
	{
		return -1;
	}
	else
	{
		memcpy(sn, tmp, 8);
		return 0;
	}
}

int writeSN(char* sn)
{
	char tmp[USER_DEVICE_ID_ADDR_LENGTH]={0};
	
	if(sn == NULL)
	{
		return -1;
	}
	
	memcpy(tmp, sn, 8);
	
	if(writeUserDeviceID(tmp)<0)
	{
		return -1;
	}	
	else
	{
		return 0;
	}	
}

int readChipID(char* chipId)
{
	return readUserPrivateID(chipId);
}

int writeChipID(char* chipId)
{
	return writeUserPrivateID(chipId);
}
