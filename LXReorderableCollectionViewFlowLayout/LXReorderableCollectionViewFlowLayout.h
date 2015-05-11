//
//  LXReorderableCollectionViewFlowLayout.h
//
//  Created by Stan Chang Khin Boon on 1/10/12.
//  Copyright (c) 2012 d--buzz. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, LXDependencyType) {
    LXDependencyTypeMaster,
    LXDependencyTypeSlave
};

@protocol LXReorderableCollectionViewDataSource;

@protocol LXReorderableCollectionViewDependencyDelegate

- (void)handleLongSelectionAtIndexPath:(NSIndexPath *)indexPath withState:(UIGestureRecognizerState)state;

- (void)handlePanDraggingAtPoint:(CGPoint)point withState:(UIGestureRecognizerState)state;

@end

@interface LXReorderableCollectionViewFlowLayout : UICollectionViewFlowLayout <UIGestureRecognizerDelegate, LXReorderableCollectionViewDependencyDelegate>

@property (assign, nonatomic) CGFloat scrollingSpeed;
@property (assign, nonatomic) UIEdgeInsets scrollingTriggerEdgeInsets;
@property (strong, nonatomic, readonly) UILongPressGestureRecognizer *longPressGestureRecognizer;
@property (strong, nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer;

@property (copy, nonatomic) void (^reorderStartAnimationBlock) (UIView *currentView);
@property (copy, nonatomic) void (^reorderCompletionAnimationBlock) (UIView *currentView);
@property (assign, nonatomic) Class gestureRecognizerIgnoreViewClass;
@property (assign, nonatomic) BOOL limitViewMovementToScrollDirection; // Defaults to NO

@property (assign, nonatomic, readonly) id<LXReorderableCollectionViewDataSource> dataSource;

@property (assign, nonatomic) LXDependencyType dependency;

@property (strong, nonatomic, readonly) NSArray *slaveDependency;

- (void)addSlaveDependency:(NSObject<LXReorderableCollectionViewDependencyDelegate> *)slaveDependency;

- (void)removeSlaveDependency:(NSObject<LXReorderableCollectionViewDependencyDelegate> *)slaveDependency;

- (void)setUpGestureRecognizersOnCollectionView __attribute__((deprecated("Calls to setUpGestureRecognizersOnCollectionView method are not longer needed as setup are done automatically through KVO.")));

@end

@protocol LXReorderableCollectionViewDataSource <NSObject>

@optional

- (void)collectionView:(UICollectionView *)collectionView itemAtIndexPath:(NSIndexPath *)fromIndexPath willMoveToIndexPath:(NSIndexPath *)toIndexPath;
- (void)collectionView:(UICollectionView *)collectionView itemAtIndexPath:(NSIndexPath *)fromIndexPath didMoveToIndexPath:(NSIndexPath *)toIndexPath;

- (BOOL)collectionView:(UICollectionView *)collectionView canMoveItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView itemAtIndexPath:(NSIndexPath *)fromIndexPath canMoveToIndexPath:(NSIndexPath *)toIndexPath;

@end

@protocol LXReorderableCollectionViewDelegateFlowLayout <UICollectionViewDelegateFlowLayout>
@optional

- (void)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout willBeginDraggingItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout didBeginDraggingItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout willEndDraggingItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout didEndDraggingItemAtIndexPath:(NSIndexPath *)indexPath;

@end