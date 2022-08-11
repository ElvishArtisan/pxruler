Name:		pxruler
Version:	0.0.0
Release:	1%{?dist}
Summary:	Ruler tools for measuring desktop elements
Group:		Development/Tools
License:	GPLv2
URL:		http://github.com/ElvishArtisan/lwmon
Source0:	%{name}-%{version}.tar.gz
BuildRequires:	qt5-qtbase-devel qt5-linguist
BuildRoot: 	/var/tmp/%{name}-0.0.0


%description
Pxruler is a set of tools for measuring the dimensions graphical desktop
elements.


%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%post
if [ -x %{_bindir}/gtk-update-icon-cache ] ; then
  %{_bindir}/gtk-update-icon-cache --quiet %{_datadir}/icons/hicolor || :
fi


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%{_bindir}/pxruler
%{_mandir}/man1/pxruler.1.gz
%doc COPYING
%doc NEWS
%doc README


%changelog
* Thu Aug 11 2022 Fred Gleason <fredg@paravelsystems.com>
-- Initial packaging.
