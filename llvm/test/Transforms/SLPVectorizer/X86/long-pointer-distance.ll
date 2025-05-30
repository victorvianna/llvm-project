; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --version 5
; RUN: opt -S --passes=slp-vectorizer -mtriple=x86_64-grtev4-linux-gnu < %s -mattr=+avx | FileCheck %s

define void @test(ptr %this) {
; CHECK-LABEL: define void @test(
; CHECK-SAME: ptr [[THIS:%.*]]) #[[ATTR0:[0-9]+]] {
; CHECK-NEXT:  [[ENTRY:.*:]]
; CHECK-NEXT:    store i64 1, ptr [[THIS]], align 8
; CHECK-NEXT:    [[B:%.*]] = getelementptr i8, ptr [[THIS]], i64 8
; CHECK-NEXT:    store i64 2, ptr [[B]], align 8
; CHECK-NEXT:    [[C:%.*]] = getelementptr i8, ptr [[THIS]], i64 4294967312
; CHECK-NEXT:    store i64 3, ptr [[C]], align 8
; CHECK-NEXT:    [[D:%.*]] = getelementptr i8, ptr [[THIS]], i64 4294967320
; CHECK-NEXT:    store i64 4, ptr [[D]], align 8
; CHECK-NEXT:    ret void
;
entry:
  store i64 1, ptr %this, align 8
  %b = getelementptr i8, ptr %this, i64 8
  store i64 2, ptr %b, align 8
  %c = getelementptr i8, ptr %this, i64 u0x100000010
  store i64 3, ptr %c, align 8
  %d = getelementptr i8, ptr %this, i64 u0x100000018
  store i64 4, ptr %d, align 8
  ret void
}

