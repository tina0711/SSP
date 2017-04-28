/*
 * product.h
 *
 *  Created on: 2017. 4. 20.
 *      Author: misa
 */

#ifndef PRODUCTLIST_H_
#define PRODUCTLIST_H_

typedef struct product
{
	char name[15];
	int count;
	int price;
	double discount;
	time_t date;

} PRODUCT;


void loadProduct();
void addProduct();
int printProductList();
int printProductRecord(PRODUCT * data);
void destroyProduct();
int getProducts(PRODUCT ** products);
void deleteProduct();
void updateProduct();
int updateFile();
void sortProductsbyName();
void sortProductsbyDate();
void sortProductsbyDiscount();
void sortProductsbyPrice();
void sortProductsbyCount();
int sortProduct();
#endif /* PRODUCTLIST_H_ */
