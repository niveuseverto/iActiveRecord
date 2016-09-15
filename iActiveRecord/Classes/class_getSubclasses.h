//
//  class_getSubclasses.h
//  iActiveRecord
//
//  Created by Alex Denisov on 21.03.12.
//  Copyright (c) 2012 okolodev.org. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

static NSArray *class_getSubclasses(Class parentClass) {
    int numClasses = objc_getClassList(NULL, 0);
    NSLog(@"Trying to allocate %d bytes", sizeof(Class) * numClasses);
    Class *classes = (__unsafe_unretained Class*)calloc(numClasses, sizeof(Class));
    numClasses = objc_getClassList(classes, numClasses);
    NSMutableArray *result = [NSMutableArray array];
    for (NSInteger i = 0; i < numClasses; i++) {
        Class superClass = classes[i];
        do {
            superClass = class_getSuperclass(superClass);
        } while (superClass && superClass != parentClass);

        if (superClass == nil) {
            continue;
        }
        [result addObject:classes[i]];
    }
    return result;
}
