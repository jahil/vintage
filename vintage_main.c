#define pr_fmt(fmt) "[" KBUILD_MODNAME "]: " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>

#include "vintage.h"

struct vintage {
	char	*msg;
	bool	first_time;
	int	current_track;
};

#define DEVICE_NAME "vintage"	/* Dev name as it appears in /proc/devices   */

extern struct vintage_track vintage_cpi_trk1;
extern struct vintage_track vintage_cpi_trk2;
//extern struct vintage_track vintage_cpi_trk3;
//extern struct vintage_track vintage_cpi_trk4;
//extern struct vintage_track vintage_cpi_trk5;
//extern struct vintage_track vintage_cpi_trk6;

static struct vintage_track *tracks[] = {&vintage_cpi_trk1,
					&vintage_cpi_trk2};
//					&vintage_cpi_trk3,
//					&vintage_cpi_trk4,
//					&vintage_cpi_trk5,
//					&vintage_cpi_trk6};

static int device_open(struct inode *inode, struct file *file)
{
	struct vintage *vintage;

	vintage = kzalloc(sizeof(*vintage), GFP_KERNEL);
	if (!vintage)
		return -ENOMEM;

	vintage->first_time = true;
	vintage->msg = tracks[0]->data;	/* track 1 */
	file->private_data = vintage;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	struct vintage *vintage = file->private_data;

	kfree(vintage);
	return 0;
}

static ssize_t device_read(struct file *file,
			   char *buffer,
			   size_t length,
			   loff_t *offset)
{
	struct vintage *vintage = file->private_data;
	int current_track = vintage->current_track;

	int bytes_read = 0;

	if (vintage->first_time == true) {
		pr_info("Now playing track %d - %s\n",
			current_track + 1, tracks[current_track]->name);
		vintage->first_time = false;
	}

	if (vintage->msg - tracks[current_track]->data >=
		tracks[current_track]->len) {
		/* End of Track.  Skip to next track, or finish if it's the last track */
		current_track++;
		if (current_track >= ARRAY_SIZE(tracks))
			current_track = 0;
		pr_info("Now playing track %d - %s\n",
			current_track + 1, tracks[current_track]->name);
		vintage->msg = tracks[current_track]->data;
		vintage->current_track = current_track;
	}

	while (length &&
		(vintage->msg - tracks[current_track]->data) <
		 tracks[current_track]->len) {
		put_user(*(vintage->msg++), buffer++);

		length--;
		bytes_read++;
	}

	return bytes_read;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	pr_err("Writing to vintage - Cycles Per Instruction isn't supported.\n");
	return -EINVAL;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static struct miscdevice vintage_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &fops,
	.mode = S_IRUGO,
};

static int vintage_init(void)
{
	int ret;

	ret = misc_register(&vintage_dev);
	if (ret) {
		pr_err("misc device register failed\n");
		return ret;
	}
	pr_info("vintage - Urdu Classical Ghazals - Kernel Module Edition - 2014\n");
	pr_info("Various Artists - Urdu Classical Ghazals by Mastero Poets\n");
	pr_info("On the web at http://vintage.co\n");
	pr_info("'ogg123 - < /dev/vintage' to play.\n");

	return 0;
}

static void vintage_exit(void)
{
	misc_deregister(&vintage_dev);
}

module_init(vintage_init);
module_exit(vintage_exit);
