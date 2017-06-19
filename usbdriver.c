/*
 * =====================================================================================
 *
 *       Filename:  usbdriver.c
 *
 *    Description:  Simple Usb Driver
 *
 *        Version:  1.0
 *        Created:  2017년 06월 19일 15시 52분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  박지호, 
 *   Organization:  
 *
 * =====================================================================================
 */


// Module 형 커널을 위해
#include <linux/module.h>
#include <linux/kernel.h>

// USB 드라이버를 만들기 위해
#include <linux/usb.h>


//USB function
static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printk(KERN_INFO ">>>>>>>>>>>>USB (%04X:%04X) is connected\n", id->idVendor, id->idProduct);
    return 0; // return 0 indicates we will manage this device
}

static void usb_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO ">>>>>>>>>>>USB is disconnected\n");
    printk(KERN_INFO ">>>>>>>>>>>Finally!!! Lecture is finished. Thanks\n"); 
}

// usb_device_id
static struct usb_device_id usb_table[] = {
    { USB_DEVICE(0x090c, 0x1000)}, // vendor_id, product_id
    {} // Terminating entry
};


MODULE_DEVICE_TABLE (usb, usb_table);

// usb_driver
static struct usb_driver jiho_driver = 
{
    .name = "OS_ASSIGNMENT",
    .id_table = usb_table, // usb_device_id
    .probe = usb_probe,
    .disconnect = usb_disconnect,
};


static int __init usb_init(void)
{
    int return_value = -1;
    printk(KERN_INFO "[Operating Systems]Now... register USB Driver\n");
    return_value = usb_register(&jiho_driver);
    printk(KERN_INFO "[Operating Systems]USB Driver registration is finished.\n");
    return return_value;
}


static void __exit usb_exit(void)
{
    printk(KERN_INFO "[Operating Systems]Now... unregister USB Driver.\n");
    usb_deregister(&jiho_driver);
    printk(KERN_INFO "[Operating Systems]USB Driver unregistration is finished.\n");
}


module_init(usb_init);
module_exit(usb_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("jihoBak");
MODULE_DESCRIPTION("FINAL Assignment for OS Lecture by Kang Profeesor");
