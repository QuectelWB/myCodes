slab
====

get_mem
----

```cpp

/***********
 *
 * running linux 1.3.1 - by Figo.Zhang
 *
 * **********/

#include <linux/version.h> 
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/mm.h>

#define PRT(a, b) pr_info("%-15s=%10d %10ld %8ld\n", a, b, (PAGE_SIZE*b)/1024, (PAGE_SIZE*b)/1024/1024)

static int __init my_init(void) 
{
	struct page *p; 
	 unsigned long i, pfn, valid = 0; 
	 int free = 0, locked = 0, reserved = 0, swapcache = 0,referenced = 0, slab = 0, private = 0, uptodate = 0, dirty = 0, active = 0, writeback = 0, mappedtodisk = 0; 
	 unsigned long num_physpages; 
	 num_physpages = get_num_physpages(); 
	 for (i = 0; i < num_physpages; i++) { 
			  /* Most of ARM systems have ARCH_PFN_OFFSET */ 
		pfn = i + ARCH_PFN_OFFSET; 
			  /* may be holes due to remapping */ 
	  	if (!pfn_valid(pfn)) 
			continue;  
		valid++; 
		p = pfn_to_page(pfn); 
		if (!p) 
		   continue; 
			  /* page_count(page) == 0 is a free page. */ 
		if (!page_count(p)) { 
			   free++; 
			   continue; 
		   	} 
		if (PageLocked(p))  
		    locked++; 
		if (PageReserved(p)) 
		    reserved++; 
		  if (PageSwapCache(p)) 
		    swapcache++; 
		  if (PageReferenced(p)) 
		    referenced++; 
		  if (PageSlab(p)) 
		    slab++; 
		  if (PagePrivate(p)) 
		    private++; 
		  if (PageUptodate(p)) 
		    uptodate++; 
		  if (PageDirty(p)) 
		    dirty++; 
		  if (PageActive(p)) 
		    active++; 
		  if (PageWriteback(p)) 
		    writeback++; 
		  if (PageMappedToDisk(p)) 
		   mappedtodisk++; 
  } 
	 pr_info("\nExamining %ld pages (num_phys_pages) = %ld MB\n", num_physpages, num_physpages * PAGE_SIZE / 1024 / 1024); 
	 pr_info("Pages with valid PFN's=%ld, = %ld MB\n", valid, valid * PAGE_SIZE / 1024 / 1024); 
	 pr_info("\n                     Pages         KB     	MB\n\n"); 
 
	PRT("free", free); 
	PRT("locked", locked); 
	PRT("reserved", reserved); 
   	PRT("swapcache", swapcache); 
	PRT("referenced", referenced); 
	PRT("slab", slab); 
	PRT("private", private); 
	PRT("uptodate", uptodate); 
	PRT("dirty", dirty); 
	PRT("active", active); 
	PRT("writeback", writeback); 
	PRT("mappedtodisk", mappedtodisk);

	return 0;
}


static void __exit my_exit(void) 
{ 
        pr_info("Module exit\n"); 
} 
 
module_init(my_init); 
module_exit(my_exit); 
 
MODULE_AUTHOR("Ben Shushu"); 
MODULE_LICENSE("GPL v2");


```


``` get memory
README      get_mem.ko
/mnt # insmod get_mem.ko
[ 1368.561393]
[ 1368.561393] Examining 25600 pages (num_phys_pages) = 100 MB
[ 1368.574298] Pages with valid PFN's=25600, = 100 MB
[ 1368.582029]
[ 1368.582029]                      Pages         KB            MB
[ 1368.582029]
[ 1368.583729] free           =     13443      53772       52
[ 1368.584021] locked         =         0          0        0
[ 1368.584283] reserved       =      3774      15096       14
[ 1368.586096] swapcache      =         0          0        0
[ 1368.586483] referenced     =      1449       5796        5
[ 1368.595650] slab           =      3376      13504       13
[ 1368.602155] private        =         0          0        0
[ 1368.604153] uptodate       =      1653       6612        6
[ 1368.605707] dirty          =      1596       6384        6
[ 1368.607410] active         =       601       2404        2
[ 1368.609367] writeback      =         0          0        0
[ 1368.611282] mappedtodisk   =         0          0        0

```
