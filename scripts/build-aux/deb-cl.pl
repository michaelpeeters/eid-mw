#!/usr/bin/perl -w

use strict;
use warnings;

use Dpkg::Changelog::Debian;
use File::Basename;

my $c = Dpkg::Changelog::Debian->new();

my $changefile;
if(defined($ARGV[0])) {
	$changefile = $ARGV[0];
} else {
	$changefile = "debian/changelog";
}
my $date = undef;
if(defined($ARGV[1])) {
	$date=$ARGV[1];
}
my $version = undef;
if(defined($ARGV[2])) {
	$version=$ARGV[2];
}

$c->load($changefile);
print "before:\n-------\n";
print $c;

my $author = 'Build Slave <buildslave@eidmw.yourict.net>';

my $entry = new Dpkg::Changelog::Entry;

if(!defined($date)) {
	open GIT, "git log --date=rfc HEAD^..HEAD |";
	while(<GIT>) {
		chomp;
		if(/^Date:\s+(.*)$/) {
			$date = $1;
		}
	}
	close GIT;
}
if(!defined($version)) {
	open my $vers, dirname($0) . "/genver.sh|";
	$version = <$vers>;
	close $vers;
	chomp $version;
}
<<<<<<< HEAD
my $distribution = "";
if(exists($ENV{TARGET}) && length($ENV{TARGET}) > 0) {
	$distribution = $ENV{TARGET} . "-";
}
$distribution .= $ENV{CODE};

my $released = "";
if(!exists($ENV{TARGET})) {
	$released = "r";
}

$entry->{header} = "eid-mw ($version-0" . $ENV{SHORT} . "$released-1) $distribution; urgency=low";
$entry->{changes} = ["  * Snapshot release"];
$entry->{trailer} = " -- $author  $date";
$entry->normalize;
unshift @{$c->{data}}, $entry;
$c->save($changefile);
print "after:\n------\n";
print $c;
